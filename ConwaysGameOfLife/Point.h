#pragma once

#include <cinttypes>

/// <summary>
/// Represents a two dimensional point in Cartesian coordinate system.
/// </summary>
struct Point
{
private:
	int32_t x;
	int32_t y;

public:
	/// <summary>
	/// Instantiates a new <see cref="Point"/> object.
	/// </summary>
	Point()
		: x(0), y(0)
	{

	}

	/// <summary>
	/// Instantiates a new <see cref="Point"/> object wit given coordinates.
	/// </summary>
	/// <param name="x">The x coordinate</param>
	/// <param name="y">The x coordinate</param>
	Point(int32_t x, int32_t y)
		: x(x), y(y)
	{

	}

	/// <summary>
	/// Gets the x coordinate value.
	/// </summary>
	inline int32_t getX() const { return x; }
	
	/// <summary>
	/// Gets the y coordinate value.
	/// </summary>
	inline int32_t getY() const { return y; }

	/// <summary>
	/// Sets the x coordinate value.
	/// </summary>
	/// <param name="value">The value to be set</param>
	inline void setX(int32_t value) { x = value; }
	
	/// <summary>
	/// Sets the y coordinate value.
	/// </summary>
	/// <param name="value">The value to be set</param>
	inline void setY(int32_t value) { y = value; }


	/// <summary>
	/// Allows for adding two points.
	/// </summary>
	inline Point operator+(Point p) const
	{
		return { x + p.x, y + p.y };
	}

	/// <summary>
	/// Allows for subtracting two points.
	/// </summary>
	inline Point operator-(Point p) const
	{
		return { x - p.x, y - p.y };
	}
};