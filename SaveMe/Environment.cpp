#include "Enviroment.h"

Environment::Environment(const sf::Vector2f position, const std::string type):
m_sprite(),
m_position(position),
m_rotation()
{
	int random = rand() % 4 + 1;
	if (type == "crater")
		m_sprite.setTexture(AssetManager::GetInstance().GetTexture("Assets/" + type + toString(random) + ".png"));
	else
		m_sprite.setTexture(AssetManager::GetInstance().GetTexture("Assets/" + type + ".png"));
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_rotation);
}

void Environment::Update(const float dt)
{
}

void Environment::Draw(sf::RenderWindow& renderer)
{
	renderer.draw(m_sprite);
}

const sf::Vector2f& Environment::GetPosition() const
{
	return m_position;
}

void Environment::SetRotation(const float rotation)
{
	m_rotation = rotation;
}