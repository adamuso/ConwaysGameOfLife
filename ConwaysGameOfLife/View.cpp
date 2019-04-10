#include "stdafx.h"
#include <Windows.h>
#include "View.h"

void View::setResult(ViewResult result)
{
	this->result = result;
}

View::View()
	: nonBlocking(false), result(ViewResult::None)
{

}

void View::setNonBlocking(bool value)
{
	nonBlocking = value;
}

void View::focus(const Ref<Control>& control)
{
	if (control)
	{
		auto parent = control->findParent<View>();

		// If control does not have this view as a parent then we cannot set its focus.
		if (!parent || parent != this)
			return;
	}

	auto currentlyFocused = focused.target();

	if (currentlyFocused == control)
		return;

	// Firstly remove focused from currently focused control.
	if (currentlyFocused)
		currentlyFocused->onLostFocus();

	focused = control;

	// Then focus the next one
	control->onGotFocus();
}

void View::initialize()
{
	Ref<Graphics> graphics = new Graphics();
	graphics->resizeDevice(getSize());
	setGraphics(graphics);
}

math::Size View::getSize() const
{
	// The view size is the same as the console size.
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	return math::Size(info.srWindow.Right + 1, info.srWindow.Bottom + 1);
}

ViewResult View::getResult() const
{
	return result;
}

const Ref<Control> View::getFocusedControl() const
{
	return focused.target();
}

Ref<Application> View::getApplication() const
{
	return application.target();
}

bool View::isNonBlocking() const
{
	return nonBlocking;
}

void View::onKeyPress(char key)
{
	auto currentlyFocused = focused.target();

	// Tab key allows for moving through children controls
	if (key == '\t')
	{
		auto children = getChildren();
	
		// When we have no children then we cannot focus anything.
		if (children.empty())
		{
			focus(nullptr);
			return;
		}

		std::size_t pos;
		
		// Gets the currently focused control position in the children vector.
		if (currentlyFocused)
			pos = std::distance(children.begin(), find(children.begin(), children.end(), currentlyFocused));
		else
			pos = -1;
		
		std::size_t start = pos;

		do
		{
			// Find the next control which have tabStop set to true.
			pos++;

			if (pos >= children.size())
				pos = 0;

			// Allows us to break when we did not find the next control.
			if (pos == start)
				return;

		} while (!children[pos]->getTabStop());

		// Focus the found children
		if (pos < children.size())
			focus(children[pos]);

		return;
	}

	// Delegate the key press to currently focused control
	if (currentlyFocused)
		currentlyFocused->onKeyPress(key);
}

void View::onResize()
{
	getGraphics()->resizeDevice(getSize());
}
