#pragma once
#include <cmath>
namespace kiko
{
	constexpr  float Pi = 3.14159265359f;
	constexpr  float TwoPi = Pi * 2;
	constexpr  float HalfPi = Pi / 2;

	constexpr  	float RadiansToDegrees(float radians) { return radians * (180.0f / Pi); };
	constexpr	float DegreesToRadians(float degrees) { return degrees * (Pi / 180); };

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}
}
