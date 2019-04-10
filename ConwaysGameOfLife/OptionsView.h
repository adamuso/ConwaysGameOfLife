#pragma once

#include "View.h"
#include "Label.h"
#include "TextBox.h"
#include "Button.h"
#include "SimulationOptions.h"

/// <summary>
/// Represents a view that displays available options to the user.
/// </summary>
class OptionsView : public View
{
private:
	Ref<Label> gridWidthLabel;
	Ref<TextBox> gridWidthTextBox;
	Ref<Label> gridHeightLabel;
	Ref<TextBox> gridHeightTextBox;
	Ref<Button> backButton;
	Ref<SimulationOptions> options;

	void onButtonClick(Ref<Object> sender);
	void onTextBoxChanged(Ref<Object> sender);
	void onGridWidthTextBoxChanged();
	void onGridHeightTextBoxChanged();

public:
	/// <summary>
	/// Instantiates a new <see cref="OptionsView"/> object with specified options.
	/// </summary>
	/// <param name="options">The options object that will be populated with user choices</param>
	OptionsView(Ref<SimulationOptions> options);

	/// <summary>
	/// Destroys the view.
	/// </summary>
	virtual ~OptionsView() override { }

	/// <summary>
	/// Overrides the method allowing for view initialization.
	/// </summary>
	void initialize() override;
};