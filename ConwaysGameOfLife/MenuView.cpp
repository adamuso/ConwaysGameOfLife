#include "stdafx.h"
#include "MenuView.h"
#include "SimulationView.h"
#include "ChooseFileView.h"
#include <functional>
#include "OptionsView.h"
#include <fstream>
#include "MessageView.h"
#include <sstream>

void MenuView::onButtonClick(Ref<Object> sender)
{
	if (sender == startButton)
	{
		getApplication()->change(new SimulationView(options));
	}
	else if (sender == exitButton)
	{
		getApplication()->back();
	}
	else if (sender == optionsButton)
	{
		getApplication()->next(new OptionsView(options));
	}
	else if (sender == loadButton)
	{
		Ref<ChooseFileView> chooseFileView = new ChooseFileView();

		getApplication()->runModal(chooseFileView);

		if (chooseFileView->getResult() == ViewResult::Accept)
			loadSimulation(chooseFileView->getFilePath());
	}
}

bool MenuView::loadSimulationData(std::ifstream & stream, int32_t width, int32_t height, Ref<uint8_t[]> data)
{
	for (int32_t y = 0; y < height; y++)
		for (int32_t x = 0; x < width; x++)
		{
			int32_t value;

			stream >> value;

			if (stream.fail())
			{
				std::stringstream str;
				str << "Blad podczas odczytywania pliku. Odczytana wartosc w siatce (" << x << ", " << y
					<< ") nie jest liczba.";

				getApplication()->runModal(
					new MessageView(str.str()));
				return false;
			}

			if (stream.fail())
			{
				getApplication()->runModal(
					new MessageView("Blad podczas odczytywania pliku. Podana wysokosc oraz szerokosc nie odpowiadaja ilosci danych w pliku."));
				return false;
			}

			data[x + y * width] = value;
		}

	return true;
}

void MenuView::initializeInfoLabels()
{
	Ref<Label> infoLabel1 = new Label();
	infoLabel1->setPosition({ 20, 3 });
	infoLabel1->setText("Klawisze: ");
	infoLabel1->setWidth(30);
	addChild(infoLabel1);

	Ref<Label> infoLabel2 = new Label();
	infoLabel2->setPosition({ 20, 4 });
	infoLabel2->setText("  Tab        - poruszanie sie po kontrolkach");
	infoLabel2->setWidth(50);
	addChild(infoLabel2);

	Ref<Label> infoLabel3 = new Label();
	infoLabel3->setPosition({ 20, 5 });
	infoLabel3->setText("  Enter      - klikniecie w przycisk");
	infoLabel3->setWidth(50);
	addChild(infoLabel3);

	Ref<Label> infoLabel4 = new Label();
	infoLabel4->setPosition({ 20, 7 });
	infoLabel4->setText("Klawisze w symulacji: ");
	infoLabel4->setWidth(50);
	addChild(infoLabel4);

	Ref<Label> infoLabel5 = new Label();
	infoLabel5->setPosition({ 20, 8 });
	infoLabel5->setText("  r          - uruchomienie symulacji ");
	infoLabel5->setWidth(50);
	addChild(infoLabel5);

	Ref<Label> infoLabel6 = new Label();
	infoLabel6->setPosition({ 20, 9 });
	infoLabel6->setText("  w, s, a, d - poruszanie sie kursorem ");
	infoLabel6->setWidth(50);
	addChild(infoLabel6);

	Ref<Label> infoLabel7 = new Label();
	infoLabel7->setPosition({ 20, 10 });
	infoLabel7->setText("  i, k, j, l - poruszanie kamera");
	infoLabel7->setWidth(50);
	addChild(infoLabel7);

	Ref<Label> infoLabel8 = new Label();
	infoLabel8->setPosition({ 20, 11 });
	infoLabel8->setText("  Spacja     - ustawianie komorki");
	infoLabel8->setWidth(50);
	addChild(infoLabel8);

	Ref<Label> infoLabel9 = new Label();
	infoLabel9->setPosition({ 20, 12 });
	infoLabel9->setText("  +, -       - przyspiesznie, zwolnienie symulacji");
	infoLabel9->setWidth(50);
	addChild(infoLabel9);

	Ref<Label> infoLabel10 = new Label();
	infoLabel10->setPosition({ 20, 13 });
	infoLabel10->setText("  ESC        - wyjscie do menu symulacji");
	infoLabel10->setWidth(50);
	addChild(infoLabel10);
}

MenuView::MenuView()
	: startButton(new Button()), optionsButton(new Button()), exitButton(new Button()), loadButton(new Button()),
	options(new SimulationOptions())
{
	
}

void MenuView::initialize()
{
	View::initialize();

	// Initialize startButton
	startButton->setPosition({ 3, 3 });
	startButton->setWidth(10);
	startButton->setText("Start");
	startButton->setOnClickHandler(std::bind(&MenuView::onButtonClick, this, std::placeholders::_1));
	addChild(startButton);

	// Initialize loadButton
	loadButton->setPosition({ 3, 5 });
	loadButton->setWidth(10);
	loadButton->setText("Wczytaj");
	loadButton->setOnClickHandler(std::bind(&MenuView::onButtonClick, this, std::placeholders::_1));
	addChild(loadButton);

	// Initialize optionsButton
	optionsButton->setPosition({ 3, 7 });
	optionsButton->setWidth(10);
	optionsButton->setText("Opcje");
	optionsButton->setOnClickHandler(std::bind(&MenuView::onButtonClick, this, std::placeholders::_1));
	addChild(optionsButton);

	// Initialize exitButton
	exitButton->setPosition({ 3, 9 });
	exitButton->setWidth(10);
	exitButton->setText("Wyjscie");
	exitButton->setOnClickHandler(std::bind(&MenuView::onButtonClick, this, std::placeholders::_1));
	addChild(exitButton);

	initializeInfoLabels();
}

void MenuView::loadSimulation(std::string fileName)
{
	std::ifstream file(fileName);

	if (file.bad())
	{
		getApplication()->runModal(
			new MessageView("Wystapil blad podczas otwierania pliku."));
		return;
	}

	int32_t width;
	int32_t height;

	file >> width;

	if (file.fail() || file.eof())
	{
		getApplication()->runModal(
			new MessageView("Blad podczas odczytywania pliku. Nie mozna odczytac szerokosci siatki."));
		return;
	}

	if (width < 10 || width > 1000)
	{
		getApplication()->runModal(
			new MessageView("Nieprawidlowe dane w pliku. Szerokosc siatki jest mniejsza od 10 lub wieksza od 1000."));
		return;
	}

	file >> height;

	if (file.fail() || file.eof())
	{
		getApplication()->runModal(
			new MessageView("Blad podczas odczytywania pliku. Nie mozna odczytac wysokosci siatki."));
		return;
	}

	if (height < 10 || height > 1000)
	{
		getApplication()->runModal(
			new MessageView("Nieprawidlowe dane w pliku. Wysokosc siatki jest mniejsza od 10 lub wieksza od 1000."));
		return;
	}

	Ref<uint8_t[]> arr = new uint8_t[width * height];

	loadSimulationData(file, width, height, arr);

	options->setGridWidth(width);
	options->setGridHeight(height);
	getApplication()->change(new SimulationView(options, arr));
}
