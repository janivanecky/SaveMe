#pragma once

#include "Animator.h"
#include "SFML\Graphics.hpp"

class Base
{
public:
	Base();
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void DrawMini(sf::RenderWindow& renderer);
private:
	Animator m_animator;
	Animator m_motherShip;
	sf::Sprite m_shadow;
};