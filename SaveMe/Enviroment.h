#pragma once

#include "SFML/Graphics.hpp"
#include "Animator.h"
#include "Drawable.h"
#include "Tools.h"

class Environment: public Drawable
{
public:
	Environment(const sf::Vector2f m_position, const std::string type);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);

	const sf::Vector2f& GetPosition() const;
	void SetRotation(const float rotation);
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float m_rotation;

};