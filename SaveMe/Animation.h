#pragma once

#include "SFML\Graphics.hpp"
#include "Time.h"
#include "AssetManager.h"

class Animation
{
public:
	Animation(const std::string name, const int frameCount, const float duration, const bool isLoop, const int eventFrame = -1, const bool trueTime = false, const int actionFrame = 0);
	sf::IntRect &GetSourceRect();
	sf::Texture &GetTexture();
	void Update(const float dt);
	bool Looped();
	bool Ended();
	void Run();
	bool EventActive();
	void Action();
private:
	sf::IntRect m_sourceRect;
	sf::Texture& m_texture;
	int m_frame;
	int m_eventFrame;
	int m_actionFrame;

	float m_duration;
	float m_time;

	float m_lastTrueTime;

	int m_size;

	bool m_isLoop;
	bool m_isTrueTime;
};