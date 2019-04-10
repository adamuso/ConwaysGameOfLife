#pragma once

#include "Control.h"
#include <functional>

/// <summary>
/// Represents a text box field which can be edited by the user..
/// </summary>
class TextBox : public Control
{
private:
	std::string text;
	uint8_t capacity;
	ConsoleStyle background;
	bool hasChanged;
	std::function<void(Ref<Object>)> onChangedHandler;

public:
	/// <summary>
	/// Instantiates a new <see cref="TextBox"/> object.
	/// </summary>
	TextBox();

	/// <summary>
	/// Destroys the text box object.
	/// </summary>
	virtual ~TextBox() override { }

	/// <summary>
	/// Sets the capacity of the text box.
	/// </summary>
	/// <param name="capacity">The capacity to set</param>
	void setCapacity(uint8_t capacity);
	
	/// <summary>
	/// Sets the on changed handler invoked when the text box has changed.
	/// </summary>
	/// <param name="handler">The handler to set</param>
	void setOnChangedHandler(std::function<void(Ref<Object>)> handler);
	
	/// <summary>
	/// Gets the text of the text box.
	/// </summary>
	std::string getText() const;
	
	/// <summary>
	/// Sets the text of the text box.
	/// </summary>
	/// <param name="value">The text to set</param>
	void setText(std::string value);

	/// <summary>
	/// Overrides the method allowing for editing the text box.
	/// </summary>
	/// <param name="key">The key that was pressed.</param>
	void onKeyPress(char key) override;

	/// <summary>
	/// Overrides the method to apply button style when unfocused.
	/// </summary>
	void onLostFocus() override;
	
	/// <summary>
	/// Overrides the method to apply button style when focused.
	/// </summary>
	void onGotFocus() override;

	/// <summary>
	/// Overrides the method allowing for the text box to be drawn.
	/// </summary>
	/// <param name="graphics">The graphics used to draw the text box.</param>
	void onDraw(Ref<Graphics>& graphics) override;
};