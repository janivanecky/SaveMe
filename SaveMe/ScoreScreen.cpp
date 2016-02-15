#include "ScoreScreen.h"

ScoreScreen::ScoreScreen():
m_scores(),
m_bg(),
m_text()
{
	m_bg.setTexture(AssetManager::GetInstance().GetTexture("Assets/bg.jpg"));
	m_bg.setOrigin(m_bg.getLocalBounds().width / 2, m_bg.getLocalBounds().height / 2);
	m_text.setFont(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf"));
}

void ScoreScreen::Draw(sf::RenderWindow& renderer)
{
	m_bg.setPosition(renderer.getView().getCenter());
	renderer.draw(m_bg);

	sf::RectangleShape scoreBorder;
	scoreBorder.setOutlineColor(sf::Color(0, 0, 0, 200));
	scoreBorder.setOutlineThickness(10);
	scoreBorder.setFillColor(sf::Color::Transparent);
	scoreBorder.setSize(sf::Vector2f(400, 500));
	scoreBorder.setOrigin(200, 250);
	scoreBorder.setPosition(renderer.getView().getCenter() + sf::Vector2f(0,20));
	renderer.draw(scoreBorder);
	scoreBorder.setOutlineColor(sf::Color::White);
	scoreBorder.setPosition(renderer.getView().getCenter());
	renderer.draw(scoreBorder);

	m_text.setCharacterSize(40);
	for (int i = 0; i < 10; i++)
	{
		m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, -240 + i * 50));
		m_text.setColor(sf::Color(0, 0, 0, 200));
		m_text.setString(toString(m_scores[i]));
		renderer.draw(m_text);
		m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, -250 + i * 50));
		m_text.setColor(sf::Color::White);
		renderer.draw(m_text);
	}
}

void ScoreScreen::Pressed(const sf::Keyboard::Key key)
{

}

const bool ScoreScreen::IsReadyForChange()
{
	return false;
}

std::shared_ptr<Screen> ScoreScreen::GetNextScreen()
{
	return Screen::NewMenuScreen();
}