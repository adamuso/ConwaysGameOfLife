#include "stdafx.h"
#include "SimulationMenuView.h"
#include "ChooseFileView.h"
#include "MenuView.h"
#include "MessageView.h"
#include <fstream>

void SimulationMenuView::onButtonClick(Ref<Object> sender)
{
	if (sender == continueButton)
	{
		getApplication()->back();
	}
	else if (sender == saveButton)
	{
		Ref<ChooseFileView> chooseFileView = new ChooseFileView();
		chooseFileView->setSaving(true);

		getApplication()->runModal(chooseFileView);

		if (chooseFileView->getResult() == ViewResult::Accept)
			saveSimulation(chooseFileView->getFilePath());
	}
	else if (sender == exitButton)
	{
		getApplication()->change(new MenuView());
	}
}

void SimulationMenuView::saveSimulation(std::string filePath)
{
	std::ofstream file(filePath);

	if (file.bad())
	{
		getApplication()->runModal(
			new MessageView("Wystapil blad podczas otwierania pliku do zapisu."));

		return;
	}

	// Saves the width and height first, then the cells data
	file << simulation->getGridWidth() << " ";
	file << simulation->getGridHeight() << " " << std::endl;

	for (int32_t y = 0; y < simulation->getGridHeight(); y++)
	{
		for (int32_t x = 0; x < simulation->getGridWidth(); x++)
		{
			file << (int32_t)simulation->getCell(x, y) << " ";

			if (file.fail())
			{
				getApplication()->runModal(
					new MessageView("Wystapil blad podczas zapisywania pliku."));

				return;
			}
		}

		file << std::endl;
	}
}

SimulationMenuView::SimulationMenuView(Ref<Simulation> simulation)
	: continueButton(new Button()), saveButton(new Button()), exitButton(new Button())
{
	this->simulation = simulation;
}

void SimulationMenuView::initialize()
{
	View::initialize();

	continueButton->setText("Wznow");
	continueButton->setWidth(6);
	continueButton->setPosition({ 3, 1 });
	continueButton->setOnClickHandler(std::bind(&SimulationMenuView::onButtonClick, this, std::placeholders::_1));
	addChild(continueButton);

	saveButton->setText("Zapisz");
	saveButton->setWidth(7);
	saveButton->setPosition({ 3, 3 });
	saveButton->setOnClickHandler(std::bind(&SimulationMenuView::onButtonClick, this, std::placeholders::_1));
	addChild(saveButton);

	exitButton->setText("Zakoncz");
	exitButton->setWidth(8);
	exitButton->setPosition({ 3, 5 });
	exitButton->setOnClickHandler(std::bind(&SimulationMenuView::onButtonClick, this, std::placeholders::_1));
	addChild(exitButton);
}
