#include "stdafx.h"
#include "TextBox.h"

TextBox::TextBox()
	: background(ConsoleStyle::BackgroundGray), capacity(0),
	  hasChanged(false)
{

}

void TextBox::setCapacity(uint8_t capacity)
{
	this->capacity = capacity;
}

void TextBox::setOnChangedHandler(std::function<void(Ref<Object>)> handler)
{
	onChangedHandler = handler;
}

std::string TextBox::getText() const
{
	return text;
}

void TextBox::setText(std::string value)
{
	text = value;
	invalidate();
}

void TextBox::onKeyPress(char key)
{
	// Backspace removes the last character, other characters greater or equal to 32 are inserted to the text.
	if (key == '\b')
	{
		if (text.size() <= 0)
			return;

		hasChanged = true;

		text.erase(text.end() - 1);
	}
	else if (key >= 32)
	{
		if (text.size() >= capacity)
			return;

		hasChanged = true;

		text.append(1, key);
	}

	invalidate();
}

void TextBox::onLostFocus()
{
	if (hasChanged && onChangedHandler)
		onChangedHandler(*this);

	getGraphics()->hideCursor();
	background = ConsoleStyle::BackgroundGray;
	invalidate();
}

void TextBox::onGotFocus()
{
	hasChanged = false;
	getGraphics()->showCursor();
	background = ConsoleStyle::BackgroundWhite;
	invalidate();
}

void TextBox::onDraw(Ref<Graphics>& graphics)
{
	int i;

	for (i = 0; i < capacity; i++)
		graphics->drawPoint(i, 0, ' ', background | ConsoleStyle::ForegroundWhite);

	for (i = 0; i < capacity && i < (int)text.size(); i++)
		graphics->drawPoint(i, 0, text[i], background | ConsoleStyle::ForegroundBlack);

	graphics->setCursorPosition({ i, 0 });
}
