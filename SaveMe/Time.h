#pragma once
#include <SFML/Graphics.hpp> 
#include "Config.h"


class Time
{
public:

	static Time& GetInstance();
	void Update();
	void Stop(const float duration);
	void Slow(const float slowRate, const float duration);
	float GetDelta();
	float GetRealTime();
	bool IsEvent();
	void SetEvent();
private:
	Time();
	Time(Time const&);
	void operator=(Time const &);

	float m_gameTime;
	float m_lastTime;
	float m_lastRealTime;
	float m_timeToUpdate;

	float m_stopTime; 

	float m_slowTime;
	float m_slowRate;
	
	sf::Clock clock;

	bool m_isEvent;
	
};