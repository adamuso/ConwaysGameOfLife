#pragma once

#include <cinttypes>
#include <math.h>
#include "Object.h"

/// <summary>
/// Represents the game of life simulation.
/// </summary>
class Simulation : public Object
{
private:
	int32_t gridWidth;
	int32_t gridHeight;
	uint8_t* grid;
	uint8_t* newGrid;
	bool isSeamless;
	int32_t  aliveCellCount;

protected:
	/// <summary>
	/// Checks if the cell at given coordinates is alive.
	/// </summary>
	/// <param name="x">The x coordinate of the cell.</param>
	/// <param name="y">The y coordinate of the cell.</param>
	virtual bool isAlive(int32_t x, int32_t y);

public:
	/// <summary>
	/// Instantiates a new <see cref="Simulation"/> object.
	/// </summary>
	Simulation();

	/// <summary>
	/// Destroys the simulation.
	/// </summary>
	virtual ~Simulation() override;

	/// <summary>
	/// Gets the cell value at given coordinates.
	/// </summary>
	/// <param name="x">The x coordinate of the cell.</param>
	/// <param name="y">The y coordinate of the cell.</param>
	uint8_t getCell(int32_t x, int32_t y) const;
	
	/// <summary>
	/// Sets the cell value at given coordinates.
	/// </summary>
	/// <param name="x">The x coordinate of the cell.</param>
	/// <param name="y">The y coordinate of the cell.</param>
	/// <param name="value">The cell value to set.</param>
	void setCell(int32_t x, int32_t y, uint8_t value);

	/// <summary>
	/// Gets the grid width.
	/// </summary>
	int32_t getGridWidth() const;
	
	/// <summary>
	/// Gets the grid height.
	/// </summary>
	int32_t getGridHeight() const;
	
	/// <summary>
	/// Sets the value indicating if the grid is seamless.
	/// </summary>
	/// <param name="value">The value to set.</param>
	void setSeamless(bool value);

	/// <summary>
	/// Gets the count of the alive cells.
	/// </summary>
	int32_t getAliveCellCount();


	/// <summary>
	/// Initializes the grid using given dimensions.
	/// </summary>
	/// <param name="width">The new width of the grid.</param>
	/// <param name="height">The new height of the grid.</param>
	void initializeGrid(int32_t width, int32_t height);
	
	/// <summary>
	/// Updates the simulation by one step.
	/// </summary>
	void update();
	
	/// <summary>
	/// Resets the simulation.
	/// </summary>
	void reset();
};