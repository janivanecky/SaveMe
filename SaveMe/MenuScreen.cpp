#include "MenuScreen.h"

std::string menuItems[4] = { "PLAY", "Credits","Exit"};
std::function<std::shared_ptr<Screen>()> menuLinks[4] = { std::bind(Screen::NewGameScreen), std::bind(Screen::NewCreditScreen), std::bind(Screen::NewExitScreen)};

MenuScreen::MenuScreen():
m_font(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf")),
m_text(),
m_selectedItem(0),
m_bg(),
m_highscore(0),
m_isReadyForChange(false)
{
	m_text.setFont(m_font);
	m_text.setColor(sf::Color(255, 255, 255, 255));
	
	m_bg.setTexture(AssetManager::GetInstance().GetTexture("Assets/bg.jpg"));
	m_bg.setOrigin(m_bg.getLocalBounds().width / 2.0f, m_bg.getLocalBounds().height / 2);

	m_highscore = ScoreManager::GetTopScores();
}

void MenuScreen::Update(const float dt)
{

}

void MenuScreen::Draw(sf::RenderWindow& renderer)
{
	sf::View bgView;
	bgView.setSize(m_bg.getTextureRect().width, m_bg.getTextureRect().height);
	renderer.setView(bgView);
	m_bg.setPosition(renderer.getView().getCenter());
	renderer.draw(m_bg);

	renderer.setView(renderer.getDefaultView());

	m_text.setCharacterSize(50);

	for (int i = 0; i < 3; i++)
	{
		m_text.setColor(sf::Color(0, 0, 0, 200));
		m_text.setString(menuItems[i]);
		m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
		m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0,-70 + i * 50 + 10));
		renderer.draw(m_text);
		if (i == m_selectedItem)
			m_text.setColor(sf::Color(255, 255, 255));
		else
			m_text.setColor(sf::Color(122, 106, 77));
		m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, -70 + i * 50));
		renderer.draw(m_text);
	}

	m_text.setCharacterSize(50);
	m_text.setString("Best mission so far: " + toString(m_highscore));
	m_text.setPosition(renderer.getView().getCenter().x, renderer.getView().getSize().y - 70);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setColor(sf::Color(0, 0, 0, 200));
	renderer.draw(m_text);
	m_text.setPosition(renderer.getView().getCenter().x, renderer.getView().getSize().y - 80);
	m_text.setColor(sf::Color::White);
	renderer.draw(m_text);

}

void MenuScreen::Pressed(const sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Up)
	{
		if (m_selectedItem > 0)
			m_selectedItem--;
	}
	if (key == sf::Keyboard::Key::Down)
	{
		if (m_selectedItem < 2)
			m_selectedItem++;
	}
	if (key == sf::Keyboard::Key::Return)
	{
		m_isReadyForChange = true;
	}
}

const bool MenuScreen::IsReadyForChange()
{
	return m_isReadyForChange;
}


std::shared_ptr<Screen> MenuScreen::GetNextScreen()
{
	return menuLinks[m_selectedItem](); // Screen::NewGameScreen();
}