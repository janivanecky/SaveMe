#include "Worm.h"

Worm::Worm(const sf::Vector2f& position) :
m_position(position),
m_animator(),
m_spawnTime(rand() % 5),
m_orientation(rand() % 2 == 0 ? 1 : -1),
m_rotation(0)
{
	m_animator.AddAnimation("move", "Assets/cerv1.png", 17, 2.0f, false);
}

void Worm::Update(const float dt)
{
	m_spawnTime -= dt;
	if (m_spawnTime <= 0)
	{
		m_animator.SetAnimation("move");
		m_spawnTime = rand() % 5 + 2;
		m_position.x += m_orientation * 80.0f;

	}
	m_animator.Update(dt);
}

void Worm::Draw(sf::RenderWindow& renderer)
{
	sf::Sprite& sprite = m_animator.GetCurrentSprite();
	sprite.setPosition(m_position);
	sprite.setScale(m_orientation, 1);
	sprite.setRotation(m_rotation);
	renderer.draw(sprite);
}

const sf::Vector2f& Worm::GetPosition() const
{
	return m_position;
}

void Worm::SetRotation(const float rotation)
{
	m_rotation = rotation;
}