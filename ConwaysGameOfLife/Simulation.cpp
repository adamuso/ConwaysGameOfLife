#include "stdafx.h"
#include "Simulation.h"

bool Simulation::isAlive(int32_t x, int32_t y)
{
	int aliveNeighboors = 0;

	// Checks all neighboors and counts only the alive ones.
	for (int xOffset = -1; xOffset <= 1; xOffset++)
	{
		for (int yOffset = -1; yOffset <= 1; yOffset++)
		{
			if (xOffset == 0 && yOffset == 0)
				continue;

			if (getCell(x + xOffset, y + yOffset) == 1)
				aliveNeighboors++;
		}
	}

	if (getCell(x, y) == 0)
	{
		// If cell is dead and have 3 alive neighboors then it will revive itself.
		if (aliveNeighboors == 3)
			return true;
	}
	else if (getCell(x, y) == 1)
	{
		// If cell is alive and have 2 or 3 alive neighboors then it stays alive.
		if (aliveNeighboors >= 2 && aliveNeighboors <= 3)
			return true;
	}

	// Otherwise the cell dies.
	return false;
}

inline uint8_t Simulation::getCell(int32_t x, int32_t y) const
{
	// Coerce the coordinates for seamless mode.
	if (isSeamless)
	{
		x = x < 0 ? gridWidth + x % gridWidth : x % gridWidth;
		y = y < 0 ? gridHeight + y % gridHeight : y % gridHeight;
	}

	if (x < 0 || x >= gridWidth)
		return 0;

	if (y < 0 || y >= gridHeight)
		return 0;

	return grid[x + y * gridWidth];
}

void Simulation::setCell(int32_t x, int32_t y, uint8_t value)
{
	// Coerce the coordinates for seamless mode.
	if (isSeamless)
	{
		x = x < 0 ? gridWidth - x % gridWidth : x % gridWidth;
		y = y < 0 ? gridHeight - y % gridHeight : y % gridHeight;
	}

	uint32_t i = x + y * gridWidth;

	grid[x + y * gridWidth] = value;
}

int32_t Simulation::getGridWidth() const
{
	return gridWidth;
}

int32_t Simulation::getGridHeight() const
{
	return gridHeight;
}

void Simulation::setSeamless(bool value) 
{ 
	isSeamless = value;
}

int32_t Simulation::getAliveCellCount() 
{ 
	return aliveCellCount; 
}

Simulation::Simulation()
{
	gridWidth = 0;
	gridHeight = 0;
	grid = nullptr;
	newGrid = nullptr;
	isSeamless = false;
}

Simulation::~Simulation()
{
	if (grid != nullptr)
		delete grid;

	if (newGrid != nullptr)
		delete newGrid;
}

void Simulation::initializeGrid(int32_t width, int32_t height)
{
	gridWidth = width;
	gridHeight = height;

	grid = new uint8_t[width * height];
	newGrid = new uint8_t[width * height];

	reset();
}

void Simulation::update()
{
	aliveCellCount = 0;

	// Update is saving the next step in the newGrid array and then this array
	// is copied to the current grid. This prevents miscalculating cell value.
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			bool alive = isAlive(x, y) ? 1 : 0;

			if (alive)
				aliveCellCount++;

			newGrid[x + y * gridWidth] = alive;
		}
	}

	for (int y = 0; y < gridHeight; y++)
		for (int x = 0; x < gridWidth; x++)
			grid[x + y * gridWidth] = newGrid[x + y * gridWidth];
}

void Simulation::reset()
{
	for (int i = 0; i < gridWidth * gridHeight; i++)
	{
		grid[i] = 0;
		newGrid[i] = 0;
	}

	aliveCellCount = 0;
}
