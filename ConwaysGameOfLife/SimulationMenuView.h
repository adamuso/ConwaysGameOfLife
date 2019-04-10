#pragma once

#include "View.h"
#include "Button.h"
#include "Simulation.h"

/// <summary>
/// Represents a menu view displayed when simulation is paused.
/// </summary>
class SimulationMenuView : public View
{
private:
	Ref<Button> continueButton;
	Ref<Button> saveButton;
	Ref<Button> exitButton;
	Ref<Simulation> simulation;

	void onButtonClick(Ref<Object> sender);
	void saveSimulation(std::string filePath);

public:
	/// <summary>
	/// Instantiates a new <see cref="SimulationMenuView"/> object with given simulation.
	/// </summary>
	/// <param name="simulation">The simulation that will be associated with the view.</param>
	SimulationMenuView(Ref<Simulation> simulation);

	/// <summary>
	/// Destroys the view.
	/// </summary>
	virtual ~SimulationMenuView() override { }

	/// <summary>
	/// Overrides the method allowing for view initialization.
	/// </summary>
	void initialize() override;
};