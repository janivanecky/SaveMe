#pragma once

#include <map>
#include <functional>

#include "Animation.h"
#include "SFML/Graphics.hpp"


class Animator
{
public:
	Animator();
	sf::Sprite& GetCurrentSprite();
	void Update(const float dt);

	void AddAnimation(const std::string name, const std::string file, const int frameCount, const float duration, const bool isLoop, const int eventFrame = -1, const bool trueTime = false, const int actionFrame = 0);
	void SetAnimation(const std::string name, const std::function<bool()> callbackFunction = nullptr, const bool isOverride = false);

	const bool Ended();
private:
	std::map<std::string, Animation *> m_animations;
	Animation *m_currentAnimation;
		
	sf::Sprite m_sprite;

	std::function<bool()> m_eventCallback;
};
