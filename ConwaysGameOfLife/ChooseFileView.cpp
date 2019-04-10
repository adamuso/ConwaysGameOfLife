#include "stdafx.h"
#include "ChooseFileView.h"
#include <fstream>

void ChooseFileView::onButtonClick(Ref<Object> sender)
{
	if (sender == acceptButton)
	{
		std::ifstream file(fileNameTextBox->getText());

		if (!isSaving)
		{
			// When we are not saving we need to check if the file exists.
			if (!file.good())
				errorLabel->setText("Podany plik nie istnieje!");
			else
			{
				setResult(ViewResult::Accept);
				getApplication()->back();
			}
		}
		else
		{
			// When we are saving we need to check if the file exists and warn the user about it.
			if (file.good() && !isOverwriting)
			{
				errorLabel->setText("Podany plik juz istnieje, aby nadpisac wcisnij przycisk Zapisz ponownie.");
				isOverwriting = true;
			}
			else
			{
				setResult(ViewResult::Accept);
				getApplication()->back();
			}
		}
	}
	else if (sender == cancelButton)
	{
		setResult(ViewResult::Cancel);
		getApplication()->back();
	}
}

ChooseFileView::ChooseFileView()
	: informationLabel(new Label()), errorLabel(new Label()), fileNameTextBox(new TextBox()),
	  acceptButton(new Button()), cancelButton(new Button()), isSaving(false), isOverwriting(false)
{

}

void ChooseFileView::setSaving(bool value)
{
	isSaving = value;
}

std::string ChooseFileView::getFilePath() const
{
	return fileNameTextBox->getText();
}

void ChooseFileView::initialize()
{
	View::initialize();

	std::string text = "Podaj sciezke do pliku, ktory chcesz ";
	text += isSaving ? "zapisac." : "otworzyc.";

	informationLabel->setPosition({ 1, 1 });
	informationLabel->setText(text);
	informationLabel->setWidth(50);
	addChild(informationLabel);

	fileNameTextBox->setPosition({ 1, 3 });
	fileNameTextBox->setCapacity(100);
	addChild(fileNameTextBox);

	errorLabel->setPosition({ 1, 5 });
	errorLabel->setWidth(100);
	errorLabel->setStyle(ConsoleStyle::ForegroundRed | ConsoleStyle::ForegroundIntensity);
	addChild(errorLabel);

	cancelButton->setPosition({ 1, 7 });
	cancelButton->setText("Anuluj");
	cancelButton->setWidth(7);
	cancelButton->setOnClickHandler(std::bind(&ChooseFileView::onButtonClick, this, std::placeholders::_1));
	addChild(cancelButton);

	acceptButton->setPosition({ 10, 7 });
	acceptButton->setText(isSaving ? "Zapisz" : "Otworz");
	acceptButton->setWidth(7);
	acceptButton->setOnClickHandler(std::bind(&ChooseFileView::onButtonClick, this, std::placeholders::_1));
	addChild(acceptButton);
}

void ChooseFileView::onKeyPress(char key)
{
	// When the tab key is pressed (the focused has will change) we need to remove the text from the
	// error label, so the overwrite message will disappear.
	if (key == '\t' && isOverwriting)
	{
		errorLabel->setText("");
		isOverwriting = false;
	}

	View::onKeyPress(key);
}
