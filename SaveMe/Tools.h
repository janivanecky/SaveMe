#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>

template<typename T>
std::string toString(T num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}


template <typename T>
typename std::vector<T>::const_iterator CheckIfNearby(const sf::Vector2f& position, std::vector<T>& vector, const float distance)
{
	float distanceToCheck = distance * distance;
	for (auto it = vector.begin(); it != vector.end(); ++it)
	{
		float dx = position.x - it->get()->GetPosition().x;
		float dy = position.y - it->get()->GetPosition().y;
		float distanceSqrd = dx * dx + dy * dy;

		if (distanceSqrd < distanceToCheck)
			return it;
	}

	return vector.end();
}