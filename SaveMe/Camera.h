#pragma once
#include "SFML\Graphics.hpp"
#include "Math.h"
#include "Time.h"


class Camera
{
public:
	static Camera& GetInstance();
	void Update(const sf::Vector2f& ship);
	void Shake(const float duration, const int magnitude = 100.0f);

	sf::Vector2f GetPosition();
	const sf::Vector2f &GetScreenSize();
private:
	Camera();

	sf::Vector2f m_center;
	sf::Vector2f m_position;
	
	float m_time;

	sf::Vector2f m_shakeOffset;
	float m_shakeTime;	

	sf::Vector2f m_screenSize;
	sf::Vector2f m_targetSize;

	float m_maxCameraOffset;
	int m_shakeMagnitude;
};