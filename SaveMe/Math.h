#pragma once
#include "SFML\Graphics.hpp"


float getLength(const sf::Vector2f& vector);
float getLengthSquared(const sf::Vector2f& vector);
float degreesToRadians(const float degrees);

template <typename T> T clamp(const T& value, const T& low, const T& high)
{
	return value < low ? low : (value > high ? high : value);
}