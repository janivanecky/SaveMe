#pragma once

#include "SFML\Graphics.hpp"

class Drawable
{
public:
	Drawable(){};
	virtual void Update(const float dt){};
	virtual void Draw(sf::RenderWindow& renderer){};
	virtual void DrawMini(sf::RenderWindow& renderer){};
	virtual const sf::Vector2f& GetPosition() const { static sf::Vector2f position; return position; };
	virtual void SetRotation(const float rotation) const{};
};