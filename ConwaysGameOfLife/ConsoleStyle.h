#pragma once

/// <summary>
/// Represents all available console styles used for changing the color and the background of displayed text.
/// </summary>
enum class ConsoleStyle : int
{
	ForegroundBlack = 0x0,
	ForegroundBlue = 0x1,
	ForegroundGreen = 0x2,
	ForegroundRed = 0x4,
	ForegroundIntensity = 0x8,
	ForegroundGray = ForegroundBlue | ForegroundGreen | ForegroundRed,
	ForegroundWhite = ForegroundGray | ForegroundIntensity,
	BackgroundBlack = 0x00,
	BackgroundBlue = 0x10,
	BackgroundGreen = 0x20,
	BackgroundRed = 0x40,
	BackgroundIntensity = 0x80,
	BackgroundGray = BackgroundBlue | BackgroundGreen | BackgroundRed,
	BackgroundWhite = BackgroundGray | BackgroundIntensity,
	Default = ForegroundBlue | ForegroundGreen | ForegroundRed
};

/// <summary>
/// Allows for combining <see cref="ConsoleStyle"/> instances.
/// </summary>
/// <param name="lhs">The first value to combine.</param>
/// <param name="rhs">The second value to combine.</param>
ConsoleStyle operator|(ConsoleStyle lhs, ConsoleStyle rhs);