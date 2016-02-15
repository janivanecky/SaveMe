#pragma once
#include "Drawable.h"
#include "Animator.h"

class Worm: public Drawable
{
public:
	Worm(const sf::Vector2f& position);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	const sf::Vector2f& GetPosition() const;
	void SetRotation(const float rotation);
private:
	sf::Vector2f m_position;
	Animator m_animator;
	float m_spawnTime;
	float m_orientation;
	float m_rotation;
};