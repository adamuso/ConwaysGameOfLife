#include "stdafx.h"
#include "OptionsView.h"
#include <string>
#include <sstream>

void OptionsView::onButtonClick(Ref<Object> sender)
{
	getApplication()->back();
}

void OptionsView::onTextBoxChanged(Ref<Object> sender)
{
	if (sender == gridWidthTextBox)
		onGridWidthTextBoxChanged();
	else if (sender == gridHeightTextBox)
		onGridHeightTextBoxChanged();
}

void OptionsView::onGridWidthTextBoxChanged()
{
	int32_t value = options->getGridWidth();

	try
	{
		value = std::stoi(gridWidthTextBox->getText());

		// We need to coerce the value before passing it to the options.
		if (value < 10)
		{
			value = 10;
			gridWidthTextBox->setText("10");
		}
		else if (value > 1000)
		{
			value = 1000;
			gridWidthTextBox->setText("1000");
		}
	}
	catch (std::exception&)
	{

	}

	options->setGridWidth(value);

	std::stringstream builder;
	builder << value;
	gridWidthTextBox->setText(builder.str());
}

void OptionsView::onGridHeightTextBoxChanged()
{
	int32_t value = options->getGridHeight();

	try
	{
		value = std::stoi(gridHeightTextBox->getText());

		// We need to coerce the value before passing it to the options.
		if (value < 10)
		{
			value = 10;
			gridHeightTextBox->setText("10");
		}
		else if (value > 1000)
		{
			value = 1000;
			gridHeightTextBox->setText("1000");
		}
	}
	catch (std::exception&)
	{

	}

	options->setGridHeight(value);

	std::stringstream builder;
	builder << value;
	gridHeightTextBox->setText(builder.str());
}

OptionsView::OptionsView(Ref<SimulationOptions> options)
	: gridWidthLabel(new Label()), gridWidthTextBox(new TextBox()), gridHeightLabel(new Label()),
	gridHeightTextBox(new TextBox()), backButton(new Button()), options(options)
{
}

void OptionsView::initialize()
{
	View::initialize();

	std::stringstream builder;

	gridWidthLabel->setText("Szerokosc siatki (10 - 1000)");
	gridWidthLabel->setWidth(30);
	gridWidthLabel->setPosition({ 3, 1 });
	addChild(gridWidthLabel);

	gridWidthTextBox->setCapacity(10);
	gridWidthTextBox->setPosition({ 3, 2 });
	gridWidthTextBox->setOnChangedHandler(std::bind(&OptionsView::onTextBoxChanged, this, std::placeholders::_1));
	builder << options->getGridWidth();
	gridWidthTextBox->setText(builder.str());
	addChild(gridWidthTextBox);

	gridHeightLabel->setText("Wysokosc siatki (10 - 1000)");
	gridHeightLabel->setWidth(30);
	gridHeightLabel->setPosition({ 3, 4 });
	addChild(gridHeightLabel);

	builder.str("");

	gridHeightTextBox->setCapacity(10);
	gridHeightTextBox->setPosition({ 3, 5 });
	gridHeightTextBox->setOnChangedHandler(std::bind(&OptionsView::onTextBoxChanged, this, std::placeholders::_1));
	builder << options->getGridHeight();
	gridHeightTextBox->setText(builder.str());
	addChild(gridHeightTextBox);

	backButton->setText("Powrot");
	backButton->setWidth(7);
	backButton->setPosition({ 3, 7 });
	backButton->setOnClickHandler(std::bind(&OptionsView::onButtonClick, this, std::placeholders::_1));
	addChild(backButton);
}
