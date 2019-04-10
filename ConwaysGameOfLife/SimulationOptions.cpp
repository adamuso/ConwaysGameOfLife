#include "stdafx.h"
#include "SimulationOptions.h"

SimulationOptions::SimulationOptions()
	: gridWidth(100), gridHeight(100)
{
}

int32_t SimulationOptions::getGridWidth() const
{
	return gridWidth;
}

void SimulationOptions::setGridWidth(int32_t value)
{
	gridWidth = value;
}

int32_t SimulationOptions::getGridHeight() const
{
	return gridHeight;
}

void SimulationOptions::setGridHeight(int32_t value)
{
	gridHeight = value;
}
