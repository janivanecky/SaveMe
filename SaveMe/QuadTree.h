#pragma once

#include "Drawable.h"
#include "Tools.h"
#include <memory>
#include <SFML/Graphics.hpp>

class QuadTree
{
public:
	void Insert(Drawable& element);
	void Clear();
	void EraseNearest(const sf::Vector2f& position, const float radius);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void DrawMini(sf::RenderWindow& renderer);
	const bool IsNear(const sf::Vector2f& position, const float radius);
	const Drawable& GetNearest(const sf::Vector2f& position, const float radius);
	const bool Contains(Drawable element);
	void Rotate(const float rotation);
private:
	std::vector<std::shared_ptr<Drawable>>& ReturnQuadrantFromPosition(const sf::Vector2f& position);
	std::vector<std::shared_ptr<Drawable>>  m_quadrant1;
	std::vector<std::shared_ptr<Drawable>>  m_quadrant2;
	std::vector<std::shared_ptr<Drawable>>  m_quadrant3;
	std::vector<std::shared_ptr<Drawable>>  m_quadrant4;

	sf::FloatRect m_viewPort;

	const bool isViewPortInQuadrant(std::vector<std::shared_ptr<Drawable>>& quadrant);
};