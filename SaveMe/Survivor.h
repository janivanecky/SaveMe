#pragma once
#include "SFML\Graphics.hpp"
#include "Animator.h"
#include "Drawable.h"
#include "Tools.h"

class Survivor: public Drawable
{
public:
	Survivor(const float x, const float y);
	Survivor(const sf::Vector2f position);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renerer);
	void DrawMini(sf::RenderWindow& renderer);
	void SetRotation(const float rotation);

	const sf::Vector2f& GetPosition() const;
	void Save(const sf::Vector2f& position) const;
	const bool IsSaved() const;
private:
	Animator m_animator;
	sf::Vector2f m_position;

	mutable const sf::Vector2f* m_safePosition;
	mutable bool m_isSafe;
	float m_timeBeingSaved;
	float m_rotation;
};