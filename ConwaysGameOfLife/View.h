#pragma once

#include "Rectangle.h"
#include "Control.h"
#include "Point.h"
#include "Application.h"
#include "Graphics.h"

/// <summary>
/// Represents a result of the view when its closed.
/// </summary>
enum class ViewResult : uint8_t
{
	None,
	Cancel,
	Accept
};

/// <summary>
/// Represents a base of all views.
/// </summary>
class View : public Control
{
	// We need to add Application class as a friend so it can inject itself into the view.
	friend class Application;

private:
	WeakRef<Application> application;
	WeakRef<Control> focused;
	bool nonBlocking;
	ViewResult result;

protected:
	/// <summary>
	/// Sets the result of the view.
	/// </summary>
	/// <param name="result">The result to set</param>
	void setResult(ViewResult result);

	/// <summary>
	/// Instantiates a new <see cref="View"/> object.
	/// </summary>
	View();

public:
	/// <summary>
	/// Destroys the view.
	/// </summary>
	virtual ~View() override { }

	/// <summary>
	/// Gets the size of the view.
	/// </summary>
	math::Size getSize() const;
	
	/// <summary>
	/// Gets the result of the view.
	/// </summary>
	ViewResult getResult() const;

	/// <summary>
	/// Gets the currently focused control.
	/// </summary>
	const Ref<Control> getFocusedControl() const;

	/// <summary>
	/// Gets the application associated with the view.
	/// </summary>
	Ref<Application> getApplication() const;

	/// <summary>
	/// Gets the value indicating if the view is in non blocking mode.
	/// </summary>
	bool isNonBlocking() const;

	/// <summary>
	/// Sets the value indicating if the view is in non blocking mode.
	/// </summary>
	/// <param name="value">The value to set</param>
	void setNonBlocking(bool value);


	/// <summary>
	/// Focuses the specified control.
	/// </summary>
	/// <param name="control">The control to focus.</param>
	void focus(const Ref<Control>& control);
	
	/// <summary>
	/// Initializes the view.
	/// </summary>
	virtual void initialize();
	
	/// <summary>
	/// Updates the view.
	/// </summary>
	virtual void update() { }

	/// <summary>
	/// Overrides the method allowing for changing currently focused control.
	/// </summary>
	void onKeyPress(char key) override;

	/// <summary>
	/// Occurs when view is resized.
	/// </summary>
	void onResize();
};