#include "Fuel.h"

Fuel::Fuel(const sf::Vector2f& position) :
m_position(position),
m_animator(),
m_rotation(0)
{
	m_animator.AddAnimation("idle", "Assets/fuel.png", 1, 1.0f, true);
	m_animator.SetAnimation("idle");
}

void Fuel::Update(const float dt)
{
	m_animator.Update(dt);
}

void Fuel::Draw(sf::RenderWindow& renderer)
{
	sf::Sprite& sprite = m_animator.GetCurrentSprite();
	sprite.setPosition(m_position);
	sprite.setRotation(m_rotation);
	renderer.draw(sprite);
}


void Fuel::DrawMini(sf::RenderWindow& renderer)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 100));
	rect.setPosition(m_position);
	rect.setFillColor(sf::Color::Green);
	rect.setOrigin(sf::Vector2f(50, 50));
	renderer.draw(rect);
}


const sf::Vector2f& Fuel::GetPosition() const
{
	return m_position;
}

void Fuel::SetRotation(const float rotation) const
{
	m_rotation = rotation;
}