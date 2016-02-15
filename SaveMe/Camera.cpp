#include "Camera.h"

Camera& Camera::GetInstance()
{
	static Camera camera;
	return camera;
}

Camera::Camera() :
m_center(0, 0),
m_position(0, 0),
m_shakeOffset(0, 0),
m_shakeTime(0),
m_time(0),
m_screenSize(DISPLAY_RESX, DISPLAY_RESY),
m_targetSize(DISPLAY_RESX, DISPLAY_RESY),
m_maxCameraOffset(0),
m_shakeMagnitude(100.0f)
{

}

void Camera::Update(const sf::Vector2f& ship)
{
	float dt = Time::GetInstance().GetRealTime() - m_time;
	m_time = Time::GetInstance().GetRealTime();

	if (m_shakeTime > 0)
	{
		m_shakeOffset = sf::Vector2f(rand() % (int)m_shakeMagnitude - m_shakeMagnitude / 2.0f,
			rand() % (int)m_shakeMagnitude - m_shakeMagnitude / 2.0f);
		m_shakeTime -= dt;
	}
	else
	{
		m_shakeOffset *= 0.97f;
	}
	m_position += (m_center - m_position) / 1.0f;
	
	m_center = ship;
}

sf::Vector2f Camera::GetPosition()
{
	return m_position + m_shakeOffset;
}

void Camera::Shake(const float duration, const int magnitude)
{
	m_shakeTime = duration;
	m_shakeMagnitude = magnitude;
}

const sf::Vector2f& Camera::GetScreenSize()
{
	return m_screenSize;
}

