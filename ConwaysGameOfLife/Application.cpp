#include "stdafx.h"
#include "Application.h"
#include <conio.h>
#include "View.h"
#include <windows.h>
#include <iostream>

void Application::updateCurrentView()
{
	if (viewStack.top()->isNonBlocking())
	{
		// When the view is non blocking firstly we need to check if key was pressed
		// if not the we update the view, otherwise we handle the pressed key.
		if (_kbhit())
		{
			char key = _getch();
			viewStack.top()->onKeyPress(key);
		}
	}
	else
	{
		// Blocking mode means that nothing happens untile the key is pressed.
		char key = _getch();
		viewStack.top()->onKeyPress(key);
	}

	// Empty view stack means that application has closed.
	if (viewStack.empty())
		return;

	viewStack.top()->update();
}

Application::Application()
	: viewStack()
{

}

void Application::setOnLoadHandler(std::function<void(const Ref<Application>& app)> handler)
{
	onLoadHandler = handler;
}

Ref<View> Application::getCurrentView() const
{
	return viewStack.top();
}

void Application::run(Ref<View> view)
{
	// For windows 8.1 and older set the buffer size width to 120.
	CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBufferInfo);

	COORD c = { 120, consoleBufferInfo.dwSize.Y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);

	// We are setting the console to fullscreen mode (only for windows 10)
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &c);
	
	change(view);
	
	// If available invokes the on load handler
	if (onLoadHandler)
		onLoadHandler(*this);

	// Main application loop
	while (!viewStack.empty())
		updateCurrentView();

	// When application is exitting turn console back to normal windowed mode.
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, &c);

	// Also we need to rollback the cursor visibility and position.
	CONSOLE_CURSOR_INFO info;
	info.bVisible = TRUE;
	info.dwSize = 10;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	c = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Application::runModal(Ref<View> view)
{
	// When a view is run as a modal, then the application waits until the modal ends.
	size_t viewStackSize = viewStack.size();
	next(view);

	// Modal view loop.
	while (viewStack.size() > viewStackSize)
		updateCurrentView();
}

void Application::change(Ref<View> view)
{
	// Changing the view means that the view will become the root of the stack. Because of that 
	// we firstly need to empty the stack.
	while (!viewStack.empty())
		viewStack.pop();

	next(view);
}

void Application::next(Ref<View> view)
{
	view->application = *this;
	view->initialize();
	view->onResize();
	viewStack.push(view);
}

void Application::back()
{
	// When the last view will be removed from the stack we clear the console because the application
	// will be closed.
	if (viewStack.size() == 1)
		viewStack.top()->getGraphics()->clear();

	viewStack.pop();

	// We need to redraw the view that is on the top on the stack for the user to see instant change.
	if (!viewStack.empty())
		viewStack.top()->invalidate();
}
