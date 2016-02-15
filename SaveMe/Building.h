#pragma once

#include "Drawable.h"
#include "Animator.h"
#include "ParticleSystem.h"
#include "Tools.h"

class Building: public Drawable
{
public:
	Building(const sf::Vector2f& position);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	const sf::Vector2f& GetPosition() const;
	const int GetSurvivorCount();
	const int GetSurvivorDistance();
private:
	Animator m_animator;
	sf::Vector2f m_position;
	ParticleSystem m_smoke;
	sf::Vector2f m_smokeOffset;

	int m_survivorCount;
	int m_survivorDistance;
};