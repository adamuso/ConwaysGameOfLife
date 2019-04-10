#include "stdafx.h"
#include "Control.h"
#include "View.h"
#include <Windows.h>
#include <vector>

ConsoleStyle operator |(ConsoleStyle lhs, ConsoleStyle rhs)
{
	return (ConsoleStyle)((int)lhs | (int)rhs);
}

Control::Control()
	: position({ 0, 0 }), tabStop(true)
{
}

void Control::setPosition(Point position)
{
	this->position = position;
}

bool Control::getTabStop() const 
{ 
	return tabStop; 
}

void Control::setTabStop(bool value) 
{
	tabStop = value; 
}

const std::vector<Ref<Control>>& Control::getChildren() const 
{
	return children;
}

const Ref<Graphics>& Control::getGraphics() const 
{
	return graphics; 
}

void Control::setGraphics(Ref<Graphics> value) 
{
	graphics = value; 
}

void Control::addChild(Ref<Control> child)
{
	if (!child)
		throw std::exception("Child cannot be null");

	std::size_t pos = (size_t)std::distance(children.begin(), std::find(children.begin(), children.end(), child));

	if (pos < children.size())
		throw std::exception("Cannot add the same child twice");

	child->parent = *this; 
	child->setGraphics(graphics);
	children.push_back(child);
	child->invalidate();
}

bool Control::isFocued() const
{
	auto view = findParent<View>();

	if (!view)
		return false;

	return view->getFocusedControl() == this;
}

void Control::invalidate() 
{ 
	if (!graphics)
		return;

	graphics->setOffset(position); 
	onDraw(graphics);
	graphics->redraw();
}

template<typename T>
inline Ref<T> Control::findParent() const
{
	Ref<Control> parent = this->parent.target();

	while (!parent.is<T>() && parent)
		parent = parent->parent.target();

	return parent.cast<T>();
}
