#include "PauseScreen.h"

std::string pauseItems[2] = { "Resume", "Back to menu"};

PauseScreen::PauseScreen(std::shared_ptr<Screen> savedScreen) :
m_text(),
m_font(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf")),
m_pausedScreen(savedScreen),
m_selectedItem(0),
m_isReadyForUnpause(false)
{
	m_text.setFont(m_font);
}

void PauseScreen::Update(const float dt)
{

}

void PauseScreen::Draw(sf::RenderWindow& renderer)
{
	renderer.setView(renderer.getDefaultView());
	m_text.setCharacterSize(100);
	m_text.setString("PAUSED");
	m_text.setColor(sf::Color(0, 0, 0, 200));
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, -renderer.getView().getCenter().y / 2 + 10));
	renderer.draw(m_text);
	m_text.setColor(sf::Color::White);
	m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, -renderer.getView().getCenter().y / 2));
	renderer.draw(m_text);

	m_text.setCharacterSize(50);
	for (int i = 0; i < 2; i++)
	{
		m_text.setColor(sf::Color(0, 0, 0, 200));
		m_text.setString(pauseItems[i]);
		m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
		m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, 50 + i * 50 + 10));
		renderer.draw(m_text);
		if (i == m_selectedItem)
			m_text.setColor(sf::Color(255, 255, 255));
		else
			m_text.setColor(sf::Color(122, 106, 77));
		m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, 50 + i * 50));
		renderer.draw(m_text);
	}
}

void PauseScreen::Pressed(const sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Up)
	{
		if (m_selectedItem > 0)
			m_selectedItem--;
	}
	if (key == sf::Keyboard::Key::Down)
	{
		if (m_selectedItem < 1)
			m_selectedItem++;
	}
	if (key == sf::Keyboard::Key::Escape || key == sf::Keyboard::Key::Return)
	{
		m_isReadyForUnpause = true;
	}
}

const bool PauseScreen::IsReadyForChange()
{
	return m_isReadyForUnpause;
}

std::shared_ptr<Screen> PauseScreen::GetNextScreen()
{
	if (m_selectedItem == 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		return m_pausedScreen;
	else
		return Screen::NewMenuScreen();
}
