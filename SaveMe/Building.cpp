#include "Building.h"

Building::Building(const sf::Vector2f& position) :
m_animator(),
m_position(position),
m_smoke("particle", 0.03f, m_position, SMOKE),
m_smokeOffset(0,0),
m_survivorCount(0),
m_survivorDistance(0)
{
	m_animator.AddAnimation("building0", "Assets/building1.png", 1, 1.0f, true);
	m_animator.AddAnimation("building1", "Assets/building2.png", 2, 1.5f, true);
	m_animator.AddAnimation("building2", "Assets/container.png", 1, 1.5f, true);
	m_animator.AddAnimation("building3", "Assets/container_broken.png", 1, 1.5f, true);
	m_animator.AddAnimation("building4", "Assets/tower.png", 2, 1.5f, true);

	int randomAnimation = rand() % 5;
	m_animator.SetAnimation("building" + toString(randomAnimation));
	if (randomAnimation == 0)
		m_smokeOffset = sf::Vector2f(20, 20);
	else
		m_smokeOffset = sf::Vector2f(-10, -80);

	switch (randomAnimation)
	{
	case 0:
		m_survivorCount = 3;
		m_survivorDistance = 120;
		break;
	case 1:
		m_survivorCount = 3;
		m_survivorDistance = 120;
		break;
	case 2:
		m_survivorCount = 1;
		m_survivorDistance = 60;
		m_smoke.Disable();
		break;
	case 3:
		m_survivorCount = 1;
		m_survivorDistance = 60;
		m_smoke.Disable();
	case 4:
		m_survivorCount = 2;
		m_survivorDistance = 100;
		m_smoke.Disable();
		break;
	}
}

void Building::Update(const float dt)
{
	m_animator.Update(dt);
	m_smoke.Update(dt, sf::Vector2f(m_smokeOffset));
	m_smoke.Emit();
}

void Building::Draw(sf::RenderWindow& renderer)
{
	sf::Sprite& sprite(m_animator.GetCurrentSprite());
	sprite.setPosition(m_position);
	renderer.draw(sprite);

	m_smoke.Draw(renderer);
}

const sf::Vector2f& Building::GetPosition() const
{
	return m_position;
}

const int Building::GetSurvivorCount()
{
	return m_survivorCount;
}

const int Building::GetSurvivorDistance()
{
	return m_survivorDistance;
}