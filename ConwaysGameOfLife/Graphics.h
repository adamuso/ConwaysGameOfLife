#pragma once

#include <vector>
#include "Point.h"
#include "ConsoleStyle.h"
#include "Rectangle.h"
#include "Object.h"

struct _CHAR_INFO;

/// <summary>
/// Represents a graphics used to manipulate the console screen.
/// </summary>
class Graphics : public Object
{
private:
	std::vector<_CHAR_INFO> pixels;
	Point offset;
	int32_t width;
	int32_t height;
	math::Rectangle viewport;
public:
	/// <summary>
	/// Instantiates a new <see cref="Graphics"/> object/
	/// </summary>
	Graphics();

	/// <summary>
	/// Destroys the graphics object.
	/// </summary>
	virtual ~Graphics() override;
	
	/// <summary>
	/// Sets the viewport used to clip the area that can be drawn.
	/// </summary>
	/// <param name="value">The rectangle to be set</param>
	void setViewport(math::Rectangle value);
	
	/// <summary>
	/// Gets the viewport data.
	/// </summary>
	const math::Rectangle& getViewport() const;

	/// <summary>
	/// Sets the cursor position in the console.
	/// </summary>
	/// <param name="position">The position to be set</param>
	void setCursorPosition(Point position) const;

	/// <summary>
	/// Sets the additional offset applied when drawing before clipping to viewport.
	/// </summary>
	/// <param name="offset">The offset to be set</param>
	void setOffset(Point offset);


	/// <summary>
	/// Redraws a point changing its shape but not the style.
	/// </summary>
	/// <param name="x">The x coordinate of the point.</param>
	/// <param name="y">The y coordinate of the point.</param>
	/// <param name="shape">The shape to be set.</param>
	void redrawPoint(int32_t x, int32_t y, char shape);

	/// <summary>
	/// Draws a point changing its shape and style.
	/// </summary>
	/// <param name="x">The x coordinate of the point.</param>
	/// <param name="y">The y coordinate of the point.</param>
	/// <param name="shape">The shape to be set.</param>
	/// <param name="style">The style to be applied.</param>
	void drawPoint(int32_t x, int32_t y, char shape, ConsoleStyle style = ConsoleStyle::Default);
	
	/// <summary>
	/// Draws a text at given position with specified style.
	/// </summary>
	/// <param name="x">The x coordinate of the text.</param>
	/// <param name="y">The y coordinate of the text.</param>
	/// <param name="text">The text to be drawn.</param>
	/// <param name="style">The style to be applied.</param>
	void drawText(int32_t x, int32_t y, std::string text, ConsoleStyle style = ConsoleStyle::Default);

	/// <summary>
	/// Clears the console.
	/// </summary>
	void clear();


	/// <summary>
	/// Shows the console cursor.
	/// </summary>
	void showCursor() const;
	
	/// <summary>
	/// Hides the console cursor.
	/// </summary>
	void hideCursor() const;

	/// <summary>
	/// Redraws the console.
	/// </summary>
	void redraw();
	
	/// <summary>
	/// Resets the viewport to its default state.
	/// </summary>
	void resetViewport();
	
	/// <summary>
	/// Resizes the device. Used to handle console size changing.
	/// </summary>
	void resizeDevice(math::Size size);
};