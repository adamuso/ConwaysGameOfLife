#pragma once

#include "Control.h"
#include <functional>

/// <summary>
/// Represents a button that cann be clicked.
/// </summary>
class Button : public Control
{
private:
	std::string text;
	int width;
	ConsoleStyle background;
	std::function<void(Ref<Object>)> onClickHandler;

public:
	/// <summary>
	/// Instantiates a new <see cref="Button"/> object.
	/// </summary>
	Button();

	/// <summary>
	/// Destroys the button.
	/// </summary>
	virtual ~Button() override { };

	/// <summary>
	/// Sets the text that will be displayed on button.
	/// </summary>
	/// <param name="text">The text to set</param>
	void setText(std::string text);

	/// <summary>
	/// Gets the text that is displayed on button.
	/// </summary>
	std::string getText();

	/// <summary>
	/// Sets the on click handler which will be invoked when the button is clicked.
	/// </summary>
	/// <param name="handler">The handler to set</param>
	void setOnClickHandler(std::function<void(Ref<Object>)> handler);

	/// <summary>
	/// Sets the width of the button.
	/// </summary>
	/// <param name="width">The width to set</param>
	void setWidth(int width);


	/// <summary>
	/// Overrides the method to allow for clicking the button.
	/// </summary>
	/// <param name="key">The key that was pressed.</param>
	void onKeyPress(char key) override;
	
	/// <summary>
	/// Overrides the method to draw the button.
	/// </summary>
	/// <param name="graphics">The graphics used to draw the button.</param>
	void onDraw(Ref<Graphics>& graphics) override;

	/// <summary>
	/// Overrides the method to apply button style when focused.
	/// </summary>
	void onGotFocus() override;
	
	/// <summary>
	/// Overrides the method to apply button style when unfocused.
	/// </summary>
	void onLostFocus() override;
};