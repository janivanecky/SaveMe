#include "Animation.h"

Animation::Animation(const std::string name, const int frameCount, const float duration, const bool isLoop, const int eventFrame, const bool trueTime, const int actionFrame) :
m_frame(0),
m_size(frameCount),
m_duration(duration),
m_time(0),
m_isLoop(isLoop),
m_eventFrame(eventFrame),
m_sourceRect(),
m_isTrueTime(trueTime),
m_lastTrueTime(0),
m_actionFrame(actionFrame),
m_texture(AssetManager::GetInstance().GetTexture(name))
{
	m_sourceRect.left = 0;
	m_sourceRect.top = 0;
	m_sourceRect.height = m_texture.getSize().y;
	m_sourceRect.width = m_texture.getSize().x / frameCount;
}

void Animation::Update(float dt)
{
	if (m_isTrueTime)
	{
		m_time += Time::GetInstance().GetRealTime() - m_lastTrueTime;
		m_lastTrueTime = Time::GetInstance().GetRealTime();
	}
	else
	{
		m_time += dt;
	}

	float timeStep = m_duration / m_size;
	m_frame = (int)floor(m_time / timeStep);

	if (m_frame >= m_size)
		m_frame = 0;

	if (m_isLoop)
	{
		if (m_time >= m_duration)
			m_time = 0;
	}

	m_sourceRect.left = m_frame * m_sourceRect.width;
}

void Animation::Run()
{
	m_time = 0;
	m_frame = 0;
	m_lastTrueTime = Time::GetInstance().GetRealTime();
}

sf::IntRect &Animation::GetSourceRect()
{
	return m_sourceRect;
}

sf::Texture &Animation::GetTexture()
{
	return m_texture;
}

bool Animation::Ended()
{
	return m_time >= m_duration;
}

bool Animation::EventActive()
{
	return m_frame >= m_eventFrame;
}

bool Animation::Looped()
{
	return m_isLoop;
}

void Animation::Action()
{
	float timeStep = m_duration / m_size;
	m_time = m_actionFrame * timeStep;
}