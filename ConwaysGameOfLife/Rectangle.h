#pragma once

#include <cinttypes>
#include "Point.h"

namespace math
{
	/// <summary>
	/// Represents a two dimensional axis aligned rectangle.
	/// </summary>
	struct Rectangle
	{
	private:
		int32_t x;
		int32_t y;
		int32_t width;
		int32_t height;

	public:
		/// <summary>
		/// Instantiates a new <see cref="Rectangle"/> object.
		/// </summary>
		Rectangle()
			:x(0), y(0), width(0), height(0)
		{

		}

		/// <summary>
		/// Instantiates a new <see cref="Rectangle"/> object with specified dimensions.
		/// </summary>
		/// <param name="x">The x coordinate of the rectangle.</param>
		/// <param name="y">The y coordinate of the rectangle.</param>
		/// <param name="width">The width of the rectangle.</param>
		/// <param name="height">The height of the rectangle.</param>
		Rectangle(int32_t x, int32_t y, int32_t width, int32_t height)
			: x(x), y(y), width(width), height(height)
		{

		}

		/// <summary>
		/// Gets the x coordinate of the rectangle.
		/// </summary>
		inline int32_t getX() const { return x; }
		
		/// <summary>
		/// Gets the y coordinate of the rectangle.
		/// </summary>
		inline int32_t getY() const { return y; }

		/// <summary>
		/// Gets the width coordinate of the rectangle.
		/// </summary>
		inline int32_t getWidth() const { return width; }

		/// <summary>
		/// Gets the height coordinate of the rectangle.
		/// </summary>
		inline int32_t getHeight() const { return height; }

		/// <summary>
		/// Gets the left side of the rectangle.
		/// </summary>
		inline int32_t getLeft() const { return x; }
		
		/// <summary>
		/// Gets the top side of the rectangle.
		/// </summary>
		inline int32_t getTop() const { return y; }

		/// <summary>
		/// Gets the right side of the rectangle.
		/// </summary>
		inline int32_t getRight() const { return x + width; }

		/// <summary>
		/// Gets the bottom side of the rectangle.
		/// </summary>
		inline int32_t getBottom() const { return y + height; }

		/// <summary>
		/// Sets the x coordinate of the rectangle.
		/// </summary>
		/// <param name="value">The value to set</param>
		inline void setX(int32_t value) { x = value; }

		/// <summary>
		/// Sets the y coordinate of the rectangle.
		/// </summary>
		/// <param name="value">The value to set</param>
		inline void setY(int32_t value) { y = value; }
		
		/// <summary>
		/// Sets the width of the rectangle.
		/// </summary>
		/// <param name="value">The value to set</param>
		inline void setWidth(int32_t value) { width = value; }

		/// <summary>
		/// Sets the height of the rectangle.
		/// </summary>
		/// <param name="value">The value to set</param>
		inline void setHeight(int32_t value) { height = value; }
		
		/// <summary>
		/// Gets the position of the rectangle.
		/// </summary>
		inline Point getPosition() const { return { x, y }; }

		/// <summary>
		/// Checks if the specfied point is contained inside the rectangle.
		/// </summary>
		/// <param name="point">The point to check</param>
		inline bool contains(Point point)
		{
			return point.getX() >= getLeft() && point.getX() <= getRight() &&
				point.getY() >= getTop() && point.getY() <= getBottom();
		}
	};

	/// <summary>
	/// Represents a size allowing for specified the dimensions.
	/// </summary>
	struct Size
	{
	private:
		int32_t width;
		int32_t height;

	public:
		/// <summary>
		/// Instantiates a new <see cref="Size"/> object.
		/// </summary>
		Size()
			: width(0), height(0)
		{

		}

		/// <summary>
		/// Instantiates a new <see cref="Size"/> with specified dimensions.
		/// </summary>
		/// <param name="width">The width value</param>
		/// <param name="height">The heightvalue</param>
		Size(int32_t width, int32_t height)
			: width(width), height(height)
		{

		}

		/// <summary>
		/// Gets the width dimension.
		/// </summary>
		inline int32_t getWidth() const { return width; }
		
		/// <summary>
		/// Gets the height dimension.
		/// </summary>
		inline int32_t getHeight() const { return height; }

		/// <summary>
		/// Sets the width dimension.
		/// </summary>
		/// <param name="value">The value to set</param>
		inline void setWidth(int32_t value) { width = value; }

		/// <summary>
		/// Sets the height dimension.
		/// </summary>
		/// <param name="value">The value to set</param>
		inline void setHeight(int32_t value) { height = value; }
	};
}