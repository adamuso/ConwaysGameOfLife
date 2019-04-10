#pragma once

#include "Utils.h"

/// <summary>
/// Represents the options for the simulation.
/// </summary>
class SimulationOptions
{
private:
	int32_t gridWidth;
	int32_t gridHeight;

public:
	/// <summary>
	/// Instantiates a new <see cref="SimulationOptions"/> object.
	/// </summary>
	SimulationOptions();

	/// <summary>
	/// Destroys the simulation options.
	/// </summary>
	~SimulationOptions() { }

	/// <summary>
	/// Gets the desired simulation grid width.
	/// </summary>
	int32_t getGridWidth() const;

	/// <summary>
	/// Sets the desired simulation grid width.
	/// </summary>
	/// <param name="value">The value to set</param>
	void setGridWidth(int32_t value);
	
	/// <summary>
	/// Gets the desired simulation grid height.
	/// </summary>
	int32_t getGridHeight() const;
	
	/// <summary>
	/// Sets the desired simulation grid height.
	/// </summary>
	/// <param name="value">The value to set</param>
	void setGridHeight(int32_t value);


};