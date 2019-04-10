#include "stdafx.h"
#include "SimulationView.h"
#include "Utils.h"
#include "Rectangle.h"
#include <sstream>
#include <vector>
#include <Windows.h>
#include "SimulationMenuView.h"

void SimulationView::drawSimulationFrame(Ref<Graphics>& graphics)
{
	int32_t frameWidth = simulation->getGridWidth() > graphics->getViewport().getWidth() - 2 
		? graphics->getViewport().getWidth() - 2 : simulation->getGridWidth();
	int32_t frameHeight = simulation->getGridHeight() > graphics->getViewport().getHeight() - 5 
		? graphics->getViewport().getHeight() - 5 : simulation->getGridHeight();

	// Draws the background and the red/green frame depending on the position of the camera. When the camera has reached its
	// limits then the red border will show up meaning that you cannot move the camera this way anymore.
	for (int32_t x = 0; x < frameWidth; x++)
	{
		if (cameraRectangle.getY() <= 0)
			graphics->drawPoint(x + 1, 3, (char)220, ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundRed);
		else
			graphics->drawPoint(x + 1, 3, (char)220, ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundGreen);
	}

	for (int32_t x = 0; x < frameWidth; x++)
	{
		if (cameraRectangle.getBottom() >= simulation->getGridHeight())
			graphics->drawPoint(x + 1, 4 + frameHeight, (char)223, ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundRed);
		else
			graphics->drawPoint(x + 1, 4 + frameHeight, (char)223, ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundGreen);
	}

	for (int32_t y = 0; y < frameHeight; y++)
	{
		if (cameraRectangle.getX() <= 0)
			graphics->drawPoint(0, 4 + y, ' ', ConsoleStyle::BackgroundRed);
		else
			graphics->drawPoint(0, 4 + y, ' ', ConsoleStyle::BackgroundGreen);
	}

	for (int32_t y = 0; y < frameHeight; y++)
	{
		if (cameraRectangle.getRight() >= simulation->getGridWidth())
			graphics->drawPoint(frameWidth + 1, 4 + y, ' ', ConsoleStyle::BackgroundRed);
		else
			graphics->drawPoint(frameWidth + 1, 4 + y, ' ', ConsoleStyle::BackgroundGreen);

	}
}

void SimulationView::drawSimulation(Ref<Graphics>& graphics)
{
	// Sets the viewport inside the simulation frame and below the information panel.
	graphics->setViewport({
		graphics->getViewport().getX() + 1,
		graphics->getViewport().getY() + 4,
		graphics->getViewport().getWidth() - 2,
		graphics->getViewport().getHeight() - 5
		});

	// Draws the simulation
	for (int32_t y = 0; y < cameraRectangle.getHeight(); y++)
	{
		for (int32_t x = 0; x < cameraRectangle.getWidth(); x++)
		{
			int32_t realX = x + cameraRectangle.getX();
			int32_t realY = y + cameraRectangle.getY();

			if (realX >= simulation->getGridWidth() || realY >= simulation->getGridHeight())
				continue;

			if (simulation->getCell(realX, realY) == 0)
				graphics->drawPoint(x, y, ' ');
			else if (simulation->getCell(realX, realY) == 1)
				graphics->drawPoint(x, y, 'O'); // ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundBlack);
		}
	}

	// Draws the cursor
	Point offsetPos = cursor - cameraRectangle.getPosition();

	if (simulation->getCell(cursor.getX(), cursor.getY()))
		graphics->drawPoint(offsetPos.getX(), offsetPos.getY(), 'X', ConsoleStyle::ForegroundRed | ConsoleStyle::ForegroundIntensity);
	else
		graphics->drawPoint(offsetPos.getX(), offsetPos.getY(), 'X', ConsoleStyle::ForegroundGreen);
}

void SimulationView::handleMovement(char key)
{
	// Handles the camera and cursor movement.
	if (key == 'a' || key == 'A')
	{
		if (cursor.getX() <= 0)
			return;

		cursor.setX(cursor.getX() - 1);
		invalidate();
	}
	else if (key == 'd' || key == 'D')
	{
		if (cursor.getX() >= simulation->getGridWidth() - 1)
			return;

		cursor.setX(cursor.getX() + 1);
		invalidate();
	}
	else if (key == 'w' || key == 'W')
	{
		if (cursor.getY() <= 0)
			return;

		cursor.setY(cursor.getY() - 1);
		invalidate();
	}
	else if (key == 's' || key == 'S')
	{
		if (cursor.getY() >= simulation->getGridHeight() - 1)
			return;

		cursor.setY(cursor.getY() + 1);
		invalidate();
	}
	else if (key == 'j' || key == 'J')
	{
		if (cameraRectangle.getX() <= 0)
			return;

		cameraRectangle.setX(cameraRectangle.getX() - 1);
		invalidate();
	}
	else if (key == 'l' || key == 'L')
	{
		if (cameraRectangle.getRight() >= simulation->getGridWidth())
			return;

		cameraRectangle.setX(cameraRectangle.getX() + 1);
		invalidate();
	}
	else if (key == 'i' || key == 'I')
	{
		if (cameraRectangle.getY() <= 0)
			return;

		cameraRectangle.setY(cameraRectangle.getY() - 1);
		invalidate();
	}
	else if (key == 'k' || key == 'K')
	{
		if (cameraRectangle.getBottom() >= simulation->getGridHeight())
			return;

		cameraRectangle.setY(cameraRectangle.getY() + 1);
		invalidate();
	}
}

const Ref<Simulation>& SimulationView::getSimulation() const 
{ 
	return simulation; 
}

SimulationView::SimulationView(Ref<SimulationOptions> options)
	: cameraRectangle(0, 0, 0, 0), simulationRunning(false), cursor({0, 0})
{
	setNonBlocking(true);

	simulation = new Simulation();
	simulation->initializeGrid(options->getGridWidth(), options->getGridHeight());

	// Load example cells
	simulation->setSeamless(true);
	simulation->setCell(2, 0, 1);
	simulation->setCell(2, 1, 1);
	simulation->setCell(2, 2, 1);
	simulation->setCell(1, 2, 1);
	simulation->setCell(0, 1, 1);
}

SimulationView::SimulationView(Ref<SimulationOptions> options, Ref<uint8_t[]> cells)
	: cameraRectangle(0, 0, 0, 0), simulationRunning(false), cursor({ 0, 0 })
{
	setNonBlocking(true);

	simulation = new Simulation();
	simulation->setSeamless(true);
	simulation->initializeGrid(options->getGridWidth(), options->getGridHeight());

	// Copy the cell data from cells array.
	for (int32_t x = 0; x < options->getGridWidth(); x++)
		for (int32_t y = 0; y < options->getGridHeight(); y++)
			simulation->setCell(x, y, cells[x + y * options->getGridWidth()]);
}

void SimulationView::setCameraSize(int32_t width, int32_t height)
{
	cameraRectangle.setWidth(width);
	cameraRectangle.setHeight(height);
}

void SimulationView::initialize()
{
	View::initialize();

	auto size = getSize();
	
	// Calculate the size of the camera based of the size of view.
	cameraRectangle = math::Rectangle(0, 0, 
		size.getWidth() - 2 < simulation->getGridWidth() ? size.getWidth() - 2 : simulation->getGridWidth(), 
		size.getHeight() - 5 < simulation->getGridHeight() ? size.getHeight() - 5: simulation->getGridHeight());

	invalidate();

	simulationSpeed = 1000;
	simulationAccumulator = 0;

	simulationTimePoint = simulationClock.now();
}

void SimulationView::moveCamera(int32_t offsetX, int32_t offsetY)
{
	int32_t newX = cameraRectangle.getX() + offsetX;
	int32_t newY = cameraRectangle.getY() + offsetY;

	cameraRectangle.setX(Utils::clamp<int32_t>(newX, 0, simulation->getGridWidth() - cameraRectangle.getWidth()));
	cameraRectangle.setY(Utils::clamp<int32_t>(newX, 0, simulation->getGridHeight() - cameraRectangle.getHeight()));
}

void SimulationView::update()
{
	// Calculate elapsed time since last invocation of update method.
	int32_t elapsedMiliseconds = (int32_t)std::chrono::duration_cast<std::chrono::milliseconds>(simulationClock.now() - simulationTimePoint).count();

	// Adjust updates to the current speed.
	if (elapsedMiliseconds >= simulationSpeed)
	{
		simulationActualMiliseconds = elapsedMiliseconds;

		if (simulationRunning)
		{
			simulation->update();
			invalidate();
			simulationAccumulator = 0;
		}

		simulationTimePoint = simulationClock.now();
	}

	// When we do not need full speed then do Sleep to give the CPU some time to think.
	if (simulationSpeed >= 100)
		Sleep(1);
}

void SimulationView::onDraw(Ref<Graphics>& graphics)
{
	graphics->resetViewport();

	// Fills the whole viewport with gray background
	for (int32_t y = 0; y < graphics->getViewport().getHeight(); y++)
	{
		for (int32_t x = 0; x < graphics->getViewport().getWidth(); x++)
		{
			graphics->drawPoint(x, y, ' ', ConsoleStyle::BackgroundGray);
		}
	}

	// Draws the information panel above the simulation.
	std::stringstream str;
	str << "Cell count: " << simulation->getAliveCellCount() << ", Simulation: " << (simulationRunning ? "running" : "paused")
		<< ", Speed: " << simulationSpeed << " ms (actual: " << simulationActualMiliseconds << " ms)";

	graphics->drawText(1, 1, str.str(), ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundBlack);

	str.str(std::string());
	str << "Camera (X, Y): " << cameraRectangle.getX() << "/" << simulation->getGridWidth() - cameraRectangle.getWidth()
		<< ", " << cameraRectangle.getY() << "/" << simulation->getGridHeight() - cameraRectangle.getHeight()
		<< "  Cursor (X, Y): " << cursor.getX() << "/" << simulation->getGridWidth() - 1
		<< ", " << cursor.getY() << "/" << simulation->getGridHeight() - 1;

	graphics->drawText(1, 2, str.str(), ConsoleStyle::BackgroundGray | ConsoleStyle::ForegroundBlack);

	// Draws the rest of the view
	drawSimulationFrame(graphics);
	drawSimulation(graphics);
}

void SimulationView::onKeyPress(char key)
{
	View::onKeyPress(key);

	if (key == 27)
		getApplication()->next(new SimulationMenuView(simulation));

	handleMovement(key);

	// Handles running the simulation, speeding up, slowing down and placing cells.
	if (key == ' ')
	{
		if(simulation->getCell(cursor.getX(), cursor.getY()))
			simulation->setCell(cursor.getX(), cursor.getY(), 0);
		else
			simulation->setCell(cursor.getX(), cursor.getY(), 1);

		invalidate();
	}
	else if (key == 'r' || key == 'R')
	{
		simulationRunning = !simulationRunning;
		invalidate();
	}
	else if (key == '-')
	{
		if (simulationSpeed >= 10000)
			return;

		simulationSpeed += 50;
		invalidate();
	}
	else if (key == '=')
	{
		if (simulationSpeed <= 1)
			return;

		simulationSpeed -= 50;
		invalidate();
	}
}
