#pragma once

#include "Point.h"
#include <vector>
#include <memory>
#include "Object.h"
#include "Graphics.h"

/// <summary>
/// Represents a control base displayed in the application.
/// </summary>
class Control : public Object
{
private:
	// The position of the control.
	Point position;
	// The weak reference to parent of the control. Weak reference is very important
	// cause we don't want to create reference cycle with our children.
	WeakRef<Control> parent;
	// Children of the control. Children are hold as strong reference because the
	// control owns its children.
	std::vector<Ref<Control>> children;
	// Indicates if the tab key should stop at this control.
	bool tabStop;
	// Graphics used for drawing on the screen.
	Ref<Graphics> graphics;

public:
	/// <summary>
	/// Instantiates a new <see cref="Control"/> object.
	/// </summary>
	Control();

	/// <summary>
	/// Destroys the control object.
	/// </summary>
	virtual ~Control() override { }

	/// <summary>
	/// Sets the position of the control.
	/// </summary>
	/// <param name="position">The positiont to set.</param>
	void setPosition(Point position);

	/// <summary>
	/// Gets the value indicating if tabbing between controls should stop at this control.
	/// </summary>
	bool getTabStop() const;

	/// <summary>
	/// Sets the value indicating if tabbing between controls should stop at his control.
	/// </summary>
	/// <param name="value">The value to set.</param>
	void setTabStop(bool value);
	
	/// <summary>
	/// Gets the children of the control.
	/// </summary>
	const std::vector<Ref<Control>>& getChildren() const;
	
	/// <summary>
	/// Gets the graphics object associated with the control.
	/// </summary>
	const Ref<Graphics>& getGraphics() const;

	/// <summary>
	/// Sets the graphics object associated with the control.
	/// </summary>
	/// <param name="value">The graphics object to set.</param>
	void setGraphics(Ref<Graphics> value);

	/// <summary>
	/// Adds a child to the control.
	/// </summary>
	/// <param name="child">The child to add.</param>
	void addChild(Ref<Control> child);


	/// <summary>
	/// Finds the parent of the given type T for the current control.
	/// </summary>
	template<typename T>
	Ref<T> findParent() const;
	
	/// <summary>
	/// Checks if the control is focused.
	/// </summary>
	bool isFocued() const;
	
	/// <summary>
	/// Invalidates the control causing it to redraw.
	/// </summary>
	void invalidate();

	/// <summary>
	/// Occurs when the control wants to redraw itself.
	/// </summary>
	/// <param name="graphics">The graphics used to draw the control.</param>
	virtual void onDraw(Ref<Graphics>& graphics) { }
	
	/// <summary>
	/// Occurs when the control receive a key press.
	/// </summary>
	/// <param name="key">The key that was pressed.</param>
	virtual void onKeyPress(char key) { }
	
	/// <summary>
	/// Occurs when the control lost focus.
	/// </summary>
	virtual void onLostFocus() { }
	
	/// <summary>
	/// Occurs when the control receive focus.
	/// </summary>
	virtual void onGotFocus() { }
};
