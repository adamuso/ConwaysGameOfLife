#pragma once

#include "View.h"
#include "Label.h"
#include "Button.h"

/// <summary>
/// Represents a view that displays a message to the user.
/// </summary>
class MessageView : public View
{
private:
	Ref<Label> textLabel;
	Ref<Button> okButton;

	void onButtonClick(Ref<Object> sender);
public:
	/// <summary>
	/// Instantiates a new <see cref="MessageView"/> object.
	/// </summary>
	MessageView(std::string text, ConsoleStyle style = ConsoleStyle::ForegroundRed | ConsoleStyle::ForegroundIntensity);

	/// <summary>
	/// Destroys the view.
	/// </summary>
	virtual ~MessageView() override { }

	/// <summary>
	/// Overrides the method allowing for view initialization.
	/// </summary>
	void initialize() override;
};