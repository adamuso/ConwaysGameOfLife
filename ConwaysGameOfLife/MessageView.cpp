#include "stdafx.h"
#include "MessageView.h"

void MessageView::onButtonClick(Ref<Object> sender)
{
	getApplication()->back();
}

MessageView::MessageView(std::string text, ConsoleStyle style)
	: textLabel(new Label()), okButton(new Button())
{
	textLabel->setText(text);
	textLabel->setStyle(style);
}

void MessageView::initialize()
{
	View::initialize();

	textLabel->setPosition({ 3, 1 });
	textLabel->setWidth(70);
	textLabel->setHeight(3);
	addChild(textLabel);

	okButton->setText("OK");
	okButton->setPosition({ 3, 5 });
	okButton->setWidth(3);
	okButton->setOnClickHandler(std::bind(&MessageView::onButtonClick, this, std::placeholders::_1));
	addChild(okButton);
}
