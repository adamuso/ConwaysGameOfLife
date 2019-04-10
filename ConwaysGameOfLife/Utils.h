#pragma once

#include <cinttypes>

/// <summary>
/// Class containing miscellaneous utility method .
/// </summary>
class Utils
{
public:
	/// <summary>
	/// Clamps the given value between min and max range.
	/// </summary>
	/// <param name="value">The value to clamp.</param>
	/// <param name="min">The minimal value.</param>
	/// <param name="max">The maximal value.</param>
	template<typename T>
	static inline T clamp(T value, T min, T max)
	{
		return value < min ? min : (value > max ? max : value);
	}
};