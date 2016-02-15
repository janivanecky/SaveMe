#include "Time.h"

Time::Time() :
m_gameTime(0),
m_stopTime(0),
m_timeToUpdate(0),
m_lastTime(0),
m_slowRate(1),
m_slowTime(0),
m_lastRealTime(0),
m_isEvent(false)
{
	clock.restart();
}

void Time::Update()
{
	m_gameTime = clock.getElapsedTime().asSeconds();
	if (m_stopTime > 0)
	{
		m_stopTime -= m_gameTime - m_lastTime;
	}
	else
	{
		m_timeToUpdate += m_gameTime - m_lastTime;
		if (m_slowTime > 0)
			m_slowTime -= m_gameTime - m_lastTime;
		else
			m_slowRate = 1;
	}
	m_lastTime = m_gameTime;
}

void Time::Stop(const float duration)
{
	m_stopTime = duration;
}

void Time::Slow(const float slowRate, const float duration)
{
	m_slowRate = slowRate;
	m_slowTime = duration;
}

Time& Time::GetInstance()
{
	static Time t;
	return t;
}

float Time::GetDelta()
{
	if (m_stopTime <= 0 && m_timeToUpdate >= UPDATE_RATE)
	{
		m_timeToUpdate -= UPDATE_RATE;
		return UPDATE_RATE / m_slowRate;
	}
	return 0;
}

float Time::GetRealTime()
{
	return m_gameTime;
}

bool Time::IsEvent()
{
	bool temp = m_isEvent;
	m_isEvent = false;
	return temp;
}

void Time::SetEvent()
{
	m_isEvent = true;
}


