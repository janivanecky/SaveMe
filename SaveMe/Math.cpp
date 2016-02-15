#include "Math.h"


float getLength(const sf::Vector2f& vector)
{
	return sqrt(getLengthSquared(vector));
}

float getLengthSquared(const sf::Vector2f& vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float degreesToRadians(const float degrees)
{
	return degrees * 3.1415f / 180.0f;
}