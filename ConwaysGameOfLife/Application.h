#pragma once

#include <stack>
#include "Object.h"
#include <functional>

class View;

/// <summary>
/// Represents an application hosting the views displayed in the console.
/// </summary>
class Application : public Object
{
private:
	std::stack<Ref<View>> viewStack;
	std::function<void(const Ref<Application>& app)> onLoadHandler;

	void updateCurrentView();
public:
	/// <summary>
	/// Instantiates a new <see cref="Application"/> object.
	/// </summary>
	Application();

	/// <summary>
	/// Destroys the application.
	/// </summary>
	virtual ~Application() override { }

	/// <summary>
	/// Sets the handler for the on load event.
	/// </summary>
	/// <param name="handler">
	/// The function that will be executed when load event occurs;
	/// </param>
	void setOnLoadHandler(std::function<void(const Ref<Application>& app)> handler);

	/// <summary>
	/// Gets the current running view.
	/// </summary>
	Ref<View> getCurrentView() const;

	/// <summary>
	/// Runs the application and takes control over the thread.
	/// </summary>
	/// <param name="view">
	/// The main view that will be displayed at the start of the application.
	/// </param>
	void run(Ref<View> view);

	/// <summary>
	/// Runs the view using modal mode. Waits untile the view exits;
	/// </summary>
	/// <param name="view">
	/// The view that will be displayed as modal view.
	/// </param>
	void runModal(Ref<View> view);

	/// <summary>
	/// Changes current view into another without saving the history.
	/// </summary>
	/// <param name="view">
	/// The view to which the current view will be changed.
	/// </param>
	void change(Ref<View> view);

	/// <summary>
	/// Changes current view to the next one and saves the last one to the history.
	/// </summary>
	/// <param name="view">
	/// The view to which the current view will be changed.
	/// </param>
	void next(Ref<View> view);

	/// <summary>
	/// Goes back in the history and loads previous view. If current view is the
	/// last one then closes the application.
	/// </summary>
	void back();
};