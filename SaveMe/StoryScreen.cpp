#include "StoryScreen.h"

StoryScreen::StoryScreen():
m_text(),
m_isReadyForChange(false)
{
	m_text.setFont(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf"));
	m_text.setColor(sf::Color::White);
}

void StoryScreen::Draw(sf::RenderWindow& renderer)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::Black);
	rect.setSize(renderer.getView().getSize());
	sf::Vector2f position(renderer.getView().getCenter() + sf::Vector2f(0, -200.0f));
	renderer.draw(rect);
	m_text.setCharacterSize(40);
	m_text.setString("2154 - Planet Gargl 22");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 70;
	m_text.setCharacterSize(20);
	m_text.setString("Colony of human excavators lives ");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("through devastating nuclear explosion.");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("Death of everyone is matter of minutes.");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("Survivors are dependent on rescue jet that is");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("to take them to galactic cruiser");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("scheduled to leave in 2 minutes.");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("Everyone needs to board cruiser and leave the planet.");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("Survival of entire population depends on rescue jet's pilot.");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
	position.y += 50;
	m_text.setCharacterSize(20);
	m_text.setString("You are that pilot.");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position);
	renderer.draw(m_text);
}

void StoryScreen::Pressed(const sf::Keyboard::Key key)
{
	m_isReadyForChange = true;
}

const bool StoryScreen::IsReadyForChange()
{
	return m_isReadyForChange;
}

std::shared_ptr<Screen> StoryScreen::GetNextScreen()
{
	return Screen::NewMenuScreen();
}