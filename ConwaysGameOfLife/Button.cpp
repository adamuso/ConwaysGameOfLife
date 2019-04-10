#include "stdafx.h"
#include "Button.h"

Button::Button()
	: text(""), width(0), background(ConsoleStyle::BackgroundGray)
{

}

void Button::setText(std::string text)
{
	this->text = text;
	this->invalidate();
}

std::string Button::getText() 
{ 
	return text; 
}

void Button::setOnClickHandler(std::function<void(Ref<Object>)> handler)
{
	onClickHandler = handler;
}

void Button::setWidth(int value)
{
	this->width = value;
	invalidate();
}

void Button::onKeyPress(char key)
{
	if (key == '\r' && onClickHandler)
		onClickHandler(*this);
}

void Button::onDraw(Ref<Graphics>& graphics)
{
	for (int i = 0; i < width; i++)
	{
		if (i < (int)text.size())
			graphics->drawPoint(i + 1, 0, text[i], background);
		else
			graphics->drawPoint(i + 1, 0, ' ', background);
	}
	
	graphics->drawPoint(0, 0, '<');
	graphics->drawPoint(width, 0, '>');
}

void Button::onGotFocus()
{
	background = ConsoleStyle::BackgroundGreen | ConsoleStyle::BackgroundBlue;
	invalidate();
}

void Button::onLostFocus()
{
	background = ConsoleStyle::BackgroundGray;
	invalidate();
}
