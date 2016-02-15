#pragma once
#include "Base.h"

Base::Base() :
m_animator(),
m_motherShip(),
m_shadow()
{
	m_animator.AddAnimation("base", "Assets/base.png", 4, 3.0f, true);
	m_animator.SetAnimation("base");

	m_motherShip.AddAnimation("idle", "Assets/cruiser.png", 4, 3.0f, true);
	m_motherShip.SetAnimation("idle");

	m_shadow.setTexture(AssetManager::GetInstance().GetTexture("Assets/cruiser_shadow.png"));
	m_shadow.setPosition(sf::Vector2f(-10,10));
	m_shadow.setOrigin(m_shadow.getTextureRect().width / 2, m_shadow.getTextureRect().height / 2);
}

void Base::Update(const float dt)
{
	m_animator.Update(dt);
	m_motherShip.Update(dt);
}

void Base::Draw(sf::RenderWindow& renderer)
{
	renderer.draw(m_shadow);
	sf::Sprite& sprite = m_animator.GetCurrentSprite();
	renderer.draw(sprite);
	sf::Sprite& motherShipSprite = m_motherShip.GetCurrentSprite();
	renderer.draw(motherShipSprite);
}

void Base::DrawMini(sf::RenderWindow& renderer)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(450, 450));
	rect.setFillColor(sf::Color::Red);
	rect.setOrigin(sf::Vector2f(225, 225));
	renderer.draw(rect);
}