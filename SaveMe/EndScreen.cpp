#include "EndScreen.h"
#include <sstream>

EndScreen::EndScreen(const int numberOfSurvivorSaved) :
m_font(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf")),
m_text(),
m_survivorsSaved(numberOfSurvivorSaved),
m_isNewHighScore(false),
m_time(1.0f)
{
	m_text.setFont(m_font);
	m_text.setColor(sf::Color(255, 255, 255, 255));
	m_text.setCharacterSize(50);
	m_isNewHighScore = ScoreManager::GetTopScores() <= numberOfSurvivorSaved;
	if (m_isNewHighScore)
		ScoreManager::SetScore(m_survivorsSaved);
}

void EndScreen::Update(const float dt)
{
	m_time += dt;
}

void EndScreen::Draw(sf::RenderWindow& renderer)
{
	renderer.setView(renderer.getDefaultView());

	sf::RectangleShape overlay;
	overlay.setSize(renderer.getView().getSize());
	overlay.setFillColor(sf::Color(0, 0, 0, 150));
	renderer.draw(overlay);

	std::stringstream ss;
	ss << "You saved " << (int)m_survivorsSaved << " survivors";

	m_text.setCharacterSize(50);
	m_text.setColor(sf::Color(0, 0, 0, 200));
	m_text.setString(ss.str());
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
	m_text.setPosition(renderer.getSize().x / 2.0f, renderer.getSize().y / 4.0f + 10);
	renderer.draw(m_text);
	m_text.setCharacterSize(30);
	m_text.setString("Press Enter To continue!");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
	m_text.setPosition(renderer.getSize().x / 2.0f, renderer.getSize().y / 4.0f + 75 + 10);
	renderer.draw(m_text);


	m_text.setCharacterSize(50);
	m_text.setColor(sf::Color::White);
	m_text.setString(ss.str());
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
	m_text.setPosition(renderer.getSize().x / 2.0f, renderer.getSize().y / 4.0f);
	renderer.draw(m_text);
	m_text.setCharacterSize(30);
	m_text.setString("Press Enter To continue!");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
	m_text.setPosition(renderer.getSize().x / 2.0f, renderer.getSize().y / 4.0f + 75);
	renderer.draw(m_text);

	if (m_isNewHighScore && (m_time > 3.14 || cos(m_time * 10.0f) < 0))
	{
		m_text.setCharacterSize(40);
		m_text.setColor(sf::Color(0, 0, 0, 200));
		m_text.setString("NEW MOST SUCCESSFULL MISSION!");
		m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
		m_text.setPosition(renderer.getSize().x / 2.0f, renderer.getSize().y / 2.0f + 10);
		renderer.draw(m_text);

		m_text.setColor(sf::Color::Yellow);
		m_text.setPosition(renderer.getSize().x / 2.0f, renderer.getSize().y / 2.0f);
		renderer.draw(m_text);
	}
}

void EndScreen::Pressed(const sf::Keyboard::Key key)
{

}

const bool EndScreen::IsReadyForChange()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}

std::shared_ptr<Screen> EndScreen::GetNextScreen()
{
	return Screen::NewGameScreen();
}