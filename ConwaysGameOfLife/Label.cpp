#include "stdafx.h"
#include "Label.h"

Label::Label()
	: style(ConsoleStyle::Default), width(0), height(1)
{ 
	setTabStop(false);
}

void Label::setStyle(ConsoleStyle value)
{
	style = value;
}

void Label::setWidth(int value)
{
	width = value;
	invalidate();
}

int Label::getWidth() const 
{ 
	return width; 
}

void Label::setHeight(int value)
{
	height = value;
}

void Label::setText(std::string value)
{
	text = value;
	invalidate();
}

std::string Label::getText() const
{
	return text;
}

void Label::onDraw(Ref<Graphics>& graphics)
{
	for (int i = 0; i < width; i++)
	{
		if (i / width >= height)
			break;

		graphics->redrawPoint(i, i / width, ' ');
	}

	for (int i = 0; i < (int)text.size(); i++)
	{
		if (i / width >= height)
			break;

		graphics->drawPoint(i, i / width, text[i], style);
	}
}
