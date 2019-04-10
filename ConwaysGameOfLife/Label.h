#pragma once

#include "Control.h"

/// <summary>
/// Represents a label displaying a static text.
/// </summary>
class Label : public Control
{
private:
	std::string text;
	int width;
	int height;
	ConsoleStyle style;

public:
	/// <summary>
	/// Instantiates a new <see cref="Label"/> object.
	/// </summary>
	Label();

	/// <summary>
	/// Destroys the label.
	/// </summary>
	virtual ~Label() override { }

	/// <summary>
	/// Sets the style for the label.
	/// </summary>
	/// <param name="value">The style to set.</param>
	void setStyle(ConsoleStyle value);
	
	/// <summary>
	/// Sets the width of the label.
	/// </summary>
	/// <param name="width">The width to set.</param>
	void setWidth(int width);
	
	/// <summary>
	/// Gets the width of the label.
	/// </summary>
	int getWidth() const;
	
	/// <summary>
	/// Sets the height of the label.
	/// </summary>
	/// <param name="value">The height set.</param>
	void setHeight(int value);

	/// <summary>
	/// Sets the displayed text of the label.
	/// </summary>
	/// <param name="text">The text to set.</param>
	void setText(std::string text);
	
	/// <summary>
	/// Gets the displayed text of the label.
	/// </summary>
	std::string getText() const;
	

	/// <summary>
	/// Overrides the method allowing the label to draw itself.
	/// </summary>
	/// <param name="graphics">The graphics used to draw the label</param>
	void onDraw(Ref<Graphics>& graphics) override;
};