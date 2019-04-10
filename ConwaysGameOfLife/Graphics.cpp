#include "stdafx.h"
#include "Graphics.h"
#include <Windows.h>

void Graphics::resizeDevice(math::Size size)
{
	pixels.resize(size.getWidth() * size.getHeight());
	width = size.getWidth();
	height = size.getHeight();

	viewport.setX(0);
	viewport.setY(0);
	viewport.setWidth(width);
	viewport.setHeight(height);
}

Graphics::Graphics()
	: viewport(0, 0, 0, 0)
{
	// When creating the graphics the cursor should be hidden
	hideCursor();
}

Graphics::~Graphics()
{
}

void Graphics::redrawPoint(int32_t x, int32_t y, char shape)
{
	x = viewport.getX() + offset.getX() + x;
	y = viewport.getY() + offset.getY() + y;

	// Check if the coordinates are contained in the viewport.
	if (x < 0 || y < 0 || x >= viewport.getRight() || x >= width || y >= viewport.getBottom() || y >= height)
		return;

	int32_t position = x + y * width;

	// Update the pixel
	auto& pixel = pixels[position];
	pixel.Char.UnicodeChar = 0;
	pixel.Char.AsciiChar = shape;
}

void Graphics::drawPoint(int32_t x, int32_t y, char shape, ConsoleStyle style)
{
	x = viewport.getX() + offset.getX() + x;
	y = viewport.getY() + offset.getY() + y;

	// Check if the coordinates are contained in the viewport.
	if (!viewport.contains({ x, y }))
		return;

	if (x < 0 || y < 0 || x >= viewport.getRight() || x >= width || y >= viewport.getBottom() || y >= height)
		return;

	int32_t position = x + y * width;

	// Update the pixel
	auto& pixel = pixels[position];
	pixel.Char.UnicodeChar = 0;
	pixel.Char.AsciiChar = shape;
	pixel.Attributes = (WORD)style;
}

void Graphics::drawText(int32_t x, int32_t y, std::string text, ConsoleStyle style)
{
	for (size_t i = 0; i < text.size(); i++)
		drawPoint(x + i, y, text[i], style);
}

void Graphics::clear()
{
	for(int32_t y = 0; y < height; y++)
		for (int32_t x = 0; x < width; x++)
		{
			auto& pixel = pixels[x + y * width];
			pixel.Char.UnicodeChar = 0;
			pixel.Char.AsciiChar = 0;
			pixel.Attributes = (WORD)ConsoleStyle::Default;
		}

	redraw();
}

void Graphics::showCursor() const
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = TRUE;
	info.dwSize = 10;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Graphics::hideCursor() const
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 10;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Graphics::setViewport(math::Rectangle value) 
{ 
	viewport = value; 
}

const math::Rectangle & Graphics::getViewport() const 
{ 
	return viewport; 
}

void Graphics::setCursorPosition(Point position) const
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), 
		{ 
			(SHORT)(position.getX() + viewport.getX() + offset.getX()), 
			(SHORT)(position.getY() + viewport.getY() + offset.getY())
		});
}

void Graphics::setOffset(Point offset)
{
	this->offset = offset;
}

void Graphics::redraw()
{
	// Redraws the whole console at once using data saved in pixels vector.
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Bottom = height;
	r.Right = width;

	WriteConsoleOutputA(GetStdHandle(STD_OUTPUT_HANDLE), &pixels[0], { (SHORT)width, (SHORT)height }, { 0, 0 }, &r);
}

void Graphics::resetViewport()
{
	viewport.setX(0);
	viewport.setY(0);
	viewport.setWidth(width);
	viewport.setHeight(height);
}
