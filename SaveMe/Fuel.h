#pragma once

#include "Drawable.h"
#include "Animator.h"

class Fuel : public Drawable
{
public:
	Fuel(const sf::Vector2f& position);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void DrawMini(sf::RenderWindow& renderer);
	const sf::Vector2f& GetPosition() const;
	void SetRotation(const float rotation) const;
private:
	Animator m_animator;
	sf::Vector2f m_position;
	mutable float m_rotation;
};