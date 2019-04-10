#pragma once

#include "View.h"
#include "Button.h"
#include "SimulationOptions.h"

/// <summary>
/// Represents a view for the main menu.
/// </summary>
class MenuView : public View
{
private:
	Ref<Button> startButton;
	Ref<Button> loadButton;
	Ref<Button> optionsButton;
	Ref<Button> exitButton;
	Ref<SimulationOptions> options;

	void onButtonClick(const Ref<Object> sender);

	bool loadSimulationData(std::ifstream& stream, int32_t width, int32_t height, Ref<uint8_t[]> data);
	void initializeInfoLabels();

public:
	/// <summary>
	/// Instantiates a new <see cref="MenuView"/> object.
	/// </summary>
	MenuView();

	/// <summary>
	/// Overrides the method allowing for view initialization.
	/// </summary>
	void initialize() override;
	
	/// <summary>
	/// Loads the simulation from the specified file.
	/// </summary>
	/// <param name="file">The file path from which the simulation will be loaded.</param>
	void loadSimulation(std::string file);
};