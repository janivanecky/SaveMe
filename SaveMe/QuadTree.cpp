#include "QuadTree.h"

void QuadTree::Insert(Drawable& element)
{
	ReturnQuadrantFromPosition(element.GetPosition()).push_back(std::shared_ptr<Drawable>(&element));
}

const bool QuadTree::IsNear(const sf::Vector2f& position, const float radius)
{
	std::vector<std::shared_ptr<Drawable>>::const_iterator foundIterator = CheckIfNearby(position, m_quadrant1, radius);
	if (foundIterator != m_quadrant1.end())
		return true;
	foundIterator = CheckIfNearby(position, m_quadrant2, radius);
	if (foundIterator != m_quadrant2.end())
		return true;
	foundIterator = CheckIfNearby(position, m_quadrant3, radius);
	if (foundIterator != m_quadrant3.end())
		return true;
	foundIterator = CheckIfNearby(position, m_quadrant4, radius);
	if (foundIterator != m_quadrant4.end())
		return true;
	return false;
}

const bool QuadTree::Contains(Drawable element)
{
	return true;
}

void QuadTree::EraseNearest(const sf::Vector2f& position, const float radius)
{
	std::vector<std::shared_ptr<Drawable>>::const_iterator foundIterator = CheckIfNearby(position, m_quadrant1, radius);
	if (foundIterator != m_quadrant1.end())
		m_quadrant1.erase(foundIterator);
	foundIterator = CheckIfNearby(position, m_quadrant2, radius);
	if (foundIterator != m_quadrant2.end())
		m_quadrant2.erase(foundIterator);
	foundIterator = CheckIfNearby(position, m_quadrant3, radius);
	if (foundIterator != m_quadrant3.end())
		m_quadrant3.erase(foundIterator);
	foundIterator = CheckIfNearby(position, m_quadrant4, radius);
	if (foundIterator != m_quadrant4.end())
		m_quadrant4.erase(foundIterator);
}

void QuadTree::Rotate(const float rotation)
{
	for (auto item : m_quadrant1)
		item->SetRotation(rotation);
	for (auto item : m_quadrant2)
		item->SetRotation(rotation);
	for (auto item : m_quadrant3)
		item->SetRotation(rotation);
	for (auto item : m_quadrant4)
		item->SetRotation(rotation);
}

void QuadTree::Update(const float dt)
{
	if (isViewPortInQuadrant(m_quadrant1))
	{
		for (auto drawable : m_quadrant1)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Update(dt);
		}
	}
	if (isViewPortInQuadrant(m_quadrant2))
	{
		for (auto drawable : m_quadrant2)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Update(dt);
		}
	}
	if (isViewPortInQuadrant(m_quadrant3))
	{
		for (auto drawable : m_quadrant3)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Update(dt);
		}
	}
	if (isViewPortInQuadrant(m_quadrant4))
	{
		for (auto drawable : m_quadrant4)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Update(dt);
		}
	}
}

void QuadTree::Draw(sf::RenderWindow& renderer)
{
	m_viewPort = sf::FloatRect(renderer.getView().getCenter() - renderer.getView().getSize(),
		renderer.getView().getSize() * 2.0f);

	if (isViewPortInQuadrant(m_quadrant1))
	{
		for (auto drawable : m_quadrant1)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Draw(renderer);
		}
	}
	if (isViewPortInQuadrant(m_quadrant2))
	{
		for (auto drawable : m_quadrant2)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Draw(renderer);
		}
	}
	if (isViewPortInQuadrant(m_quadrant3))
	{
		for (auto drawable : m_quadrant3)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Draw(renderer);
		}
	}
	if (isViewPortInQuadrant(m_quadrant4))
	{
		for (auto drawable : m_quadrant4)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->Draw(renderer);
		}
	}
}

void QuadTree::DrawMini(sf::RenderWindow& renderer)
{
	m_viewPort = sf::FloatRect(renderer.getView().getCenter() - renderer.getView().getSize(),
		renderer.getView().getSize() * 1.5f);

	if (isViewPortInQuadrant(m_quadrant1))
	{
		for (auto drawable : m_quadrant1)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->DrawMini(renderer);
		}
	}
	if (isViewPortInQuadrant(m_quadrant2))
	{
		for (auto drawable : m_quadrant2)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->DrawMini(renderer);
		}
	}
	if (isViewPortInQuadrant(m_quadrant3))
	{
		for (auto drawable : m_quadrant3)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->DrawMini(renderer);
		}
	}
	if (isViewPortInQuadrant(m_quadrant4))
	{
		for (auto drawable : m_quadrant4)
		{
			if (m_viewPort.contains(drawable->GetPosition()))
				drawable->DrawMini(renderer);
		}
	}
}

std::vector<std::shared_ptr<Drawable>>& QuadTree::ReturnQuadrantFromPosition(const sf::Vector2f& position)
{
	if (position.x >= 0 && position.y >= 0)
	{
		return m_quadrant1;
	}
	else if (position.x >= 0 && position.y < 0)
	{
		return m_quadrant2;
	}
	else if (position.x < 0 && position.y < 0)
	{
		return m_quadrant3;
	}
	else if (position.x < 0 && position.y >= 0)
	{
		return m_quadrant4;
	}
}

const Drawable& QuadTree::GetNearest(const sf::Vector2f& position, const float radius)
{
	std::vector<std::shared_ptr<Drawable>>::const_iterator foundIterator = CheckIfNearby(position, m_quadrant1, radius);
	if (foundIterator != m_quadrant1.end())
		return *foundIterator->get();
	foundIterator = CheckIfNearby(position, m_quadrant2, radius);
	if (foundIterator != m_quadrant2.end())
		return *foundIterator->get();
	foundIterator = CheckIfNearby(position, m_quadrant3, radius);
	if (foundIterator != m_quadrant3.end())
		return *foundIterator->get();
	foundIterator = CheckIfNearby(position, m_quadrant4, radius);
	return *foundIterator->get();
}

const bool QuadTree::isViewPortInQuadrant(std::vector<std::shared_ptr<Drawable>>& quadrant)
{
	sf::Vector2f leftTop(m_viewPort.left, m_viewPort.top);
	sf::Vector2f leftBot(m_viewPort.left, m_viewPort.top + m_viewPort.height);
	sf::Vector2f rightTop(m_viewPort.left + m_viewPort.width, m_viewPort.top);
	sf::Vector2f rightBot(m_viewPort.left + m_viewPort.width, m_viewPort.top + m_viewPort.height);
	if (ReturnQuadrantFromPosition(leftTop) == quadrant)
		return true;
	if (ReturnQuadrantFromPosition(leftBot) == quadrant)
		return true;
	if (ReturnQuadrantFromPosition(rightTop) == quadrant)
		return true;
	if (ReturnQuadrantFromPosition(rightBot) == quadrant)
		return true;

	return false;
}