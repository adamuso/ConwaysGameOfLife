#pragma once

#include "View.h"
#include "TextBox.h"
#include "Button.h"
#include "Label.h"

/// <summary>
/// Represents a view that allows user to choose a file.
/// </summary>
class ChooseFileView : public View
{
private:
	Ref<Label> informationLabel;
	Ref<Label> errorLabel;
	Ref<TextBox> fileNameTextBox;
	Ref<Button> acceptButton;
	Ref<Button> cancelButton;
	bool isSaving;
	bool isOverwriting;

	void onButtonClick(Ref<Object> sender);

public:
	/// <summary>
	/// Instantiates a new <see cref="ChooseFileView"/> object.
	/// </summary>
	ChooseFileView();

	/// <summary>
	/// Destroys the choose file view.
	/// </summary>
	virtual ~ChooseFileView() override { }

	/// <summary>
	/// Sets the value indicating that the view chooses a file to save and not to open.
	/// </summary>
	/// <param name="value">The value to set.</param>
	void setSaving(bool value);

	/// <summary>
	/// Gets the chosen file path.
	/// </summary>
	std::string getFilePath() const;

	/// <summary>
	/// Overrides the method to make view initialization.
	/// </summary>
	void initialize() override;

	/// <summary>
	/// Overrides the method allowing for view specific key responses.
	/// </summary>
	void onKeyPress(char key) override;
};