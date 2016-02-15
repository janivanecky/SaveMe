#include "Survivor.h"

Survivor::Survivor(const float x, const float y) :
m_animator(),
m_position(x, y),
m_safePosition(), 
m_isSafe(false),
m_rotation(),
m_timeBeingSaved(0),
Drawable()
{
	m_animator.AddAnimation("wave", "Assets/survivor.png", 8, 1.0f, true);

	m_animator.SetAnimation("wave");
}

Survivor::Survivor(const sf::Vector2f position) :
m_animator(),
m_position(position),
m_safePosition(),
m_isSafe(false),
m_rotation(),
Drawable()
{
	m_animator.AddAnimation("wave1", "Assets/survivor1.png", 8, .5f, true);
	m_animator.AddAnimation("wave2", "Assets/survivor2.png", 8, 2.0f, true);
	m_animator.AddAnimation("wave3", "Assets/survivor3.png", 14, 2.5f, true);

	int random = rand() % 3 + 1;

	m_animator.SetAnimation("wave" + toString(random));
}

void Survivor::Update(const float dt)
{
	m_animator.Update(dt);
	if (m_isSafe)
	{
		m_timeBeingSaved += dt;
		m_position += (*m_safePosition - m_position) / (2.0f / m_timeBeingSaved);
	}
}

void Survivor::Draw(sf::RenderWindow& renderer)
{
	sf::Sprite& sprite = m_animator.GetCurrentSprite();
	sprite.setPosition(m_position);
	sprite.setRotation(m_rotation);
	sprite.setOrigin(sf::Vector2f(sprite.getTextureRect().width / 2, sprite.getTextureRect().height));
	renderer.draw(sprite);
}

void Survivor::SetRotation(const float rotation)
{
	m_rotation = rotation;
}

void Survivor::DrawMini(sf::RenderWindow& renderer)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(100, 100));
	rect.setPosition(m_position);
	rect.setFillColor(sf::Color::Yellow);
	rect.setOrigin(sf::Vector2f(50, 50));
	renderer.draw(rect);
}

void Survivor::Save(const sf::Vector2f& position) const
{
	m_safePosition = &position;
	m_isSafe = true;
}

const sf::Vector2f& Survivor::GetPosition() const
{
	return m_position;
}

const bool Survivor::IsSaved() const
{
	return m_isSafe;
}