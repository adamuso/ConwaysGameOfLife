#pragma once

#include "Simulation.h"
#include "Rectangle.h"
#include "View.h"
#include <chrono>
#include "SimulationOptions.h"

/// <summary>
/// Represents the view displaying the simulation.
/// </summary>
class SimulationView : public View
{
private:
	Ref<Simulation> simulation;

	math::Rectangle cameraRectangle;
	Point cursor;
	bool simulationRunning;
	int32_t simulationSpeed;
	int32_t simulationAccumulator;
	std::chrono::high_resolution_clock simulationClock;
	std::chrono::high_resolution_clock::time_point simulationTimePoint;
	int32_t simulationActualMiliseconds;

	void drawSimulationFrame(Ref<Graphics>& graphics);
	void drawSimulation(Ref<Graphics>& graphics);
	void handleMovement(char key);

public:
	/// <summary>
	/// Instantiates the <see cref="SimulationView"/> using given options.
	/// </summary>
	/// <param name="options">The options used to create the simulation.</param>

	SimulationView(Ref<SimulationOptions> options);
	/// <summary>
	/// Instantiates the <see cref="SimulationView"/> using given options and cell data.
	/// </summary>
	/// <param name="options">The options used to create the simulation.</param>
	/// <param name="cells">The cell data used to populate the simulation.</param>
	SimulationView(Ref<SimulationOptions> options, Ref<uint8_t[]> cells);

	/// <summary>
	/// Destroys the simulation view.
	/// </summary>
	virtual ~SimulationView() override { }

	/// <summary>
	/// Gets the simulation.
	/// </summary>
	const Ref<Simulation>& getSimulation() const;
	
	/// <summary>
	/// Sets the size of the camera.
	/// </summary>
	/// <param name="width">The new width of the camera.</param>
	/// <param name="height">The new height of the camera.</param>
	void setCameraSize(int32_t width, int32_t height);

	/// <summary>
	/// Overrides the method allowing for view initialization.
	/// </summary>
	void initialize() override;

	/// <summary>
	/// Moves the camera by the specified offset.
	/// </summary>
	void moveCamera(int32_t offsetX, int32_t offsetY);

	/// <summary>
	/// Overrides the method allowing for simulation updating.
	/// </summary>
	void update() override;
	
	/// <summary>
	/// Overrides the method allowing for simulation to be drawn.
	/// </summary>
	void onDraw(Ref<Graphics>& graphics) override;

	/// <summary>
	/// Overrides the method allowing for simulation manipulation with key presses.
	/// </summary>
	void onKeyPress(char key) override;
};