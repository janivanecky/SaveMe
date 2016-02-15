#include "Animator.h"

Animator::Animator():
m_currentAnimation(NULL)
{
}

void Animator::Update(const float dt)
{
	if (m_currentAnimation != NULL)
	{
		m_currentAnimation->Update(dt);

		m_sprite.setTextureRect(m_currentAnimation->GetSourceRect());

		if (m_eventCallback && m_currentAnimation->EventActive())
		{
			if (m_eventCallback())
			{
				m_currentAnimation->Action();
				m_eventCallback = nullptr;
			}
		}
		if (m_currentAnimation->Ended())
			m_eventCallback = nullptr;

		if (m_currentAnimation->Ended() && !m_currentAnimation->Looped())
		{
			m_currentAnimation = NULL;
			m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
		}
	}
}

void Animator::AddAnimation(const std::string name, const std::string file, const int frameCount, const float duration, const bool isLoop, const int eventFrame, const bool trueTime, const int actionFrame)
{
	m_animations.emplace(name, new Animation(file, frameCount, duration, isLoop, eventFrame, trueTime, actionFrame));
}

void Animator::SetAnimation(const std::string name, const std::function<bool(void)> callbackFunction, const bool isOverride)
{
	if (isOverride || m_currentAnimation == NULL || m_currentAnimation->Looped() ||
		(!m_currentAnimation->Looped() && !m_animations.at(name)->Looped()))
	{
			if (m_currentAnimation != m_animations.at(name))
		{
			m_currentAnimation = m_animations.at(name);
			if (!m_currentAnimation->Looped())
				m_currentAnimation->Run();
			m_eventCallback = callbackFunction;
			m_sprite.setTexture(m_currentAnimation->GetTexture());
			m_sprite.setTextureRect(m_currentAnimation->GetSourceRect());
			m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.0f, m_sprite.getTextureRect().height / 2.0f);
		}
	}
}

sf::Sprite& Animator::GetCurrentSprite()
{
	return m_sprite;
}

const bool Animator::Ended()
{
	return m_currentAnimation == NULL || m_currentAnimation->Ended();
}

