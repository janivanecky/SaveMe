#include "CreditScreen.h"

CreditScreen::CreditScreen() :
m_font(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf")),
m_text(),
m_bg()
{
	m_text.setFont(m_font);
	m_bg.setTexture(AssetManager::GetInstance().GetTexture("Assets/bg.jpg"));
	m_bg.setOrigin(m_bg.getTextureRect().width / 2, m_bg.getTextureRect().height / 2);
}

void CreditScreen::Update(const float dt)
{

}

void CreditScreen::Draw(sf::RenderWindow& renderer)
{
	sf::View bgView;
	bgView.setSize(m_bg.getTextureRect().width, m_bg.getTextureRect().height);
	renderer.setView(bgView);
	m_bg.setPosition(renderer.getView().getCenter());
	renderer.draw(m_bg);

	m_text.setColor(sf::Color(0, 0, 0, 200));


	sf::Vector2f position = renderer.getView().getCenter() + sf::Vector2f(0, -renderer.getView().getSize().y / 6.0f);
	m_text.setCharacterSize(100);
	m_text.setString("Credits");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 150;
	m_text.setCharacterSize(60);
	m_text.setString("Game By:");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 70;
	m_text.setCharacterSize(50);
	m_text.setString("Jan Ivanecky");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 70;
	m_text.setCharacterSize(50);
	m_text.setString("Michal Ivanecky");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 100;
	m_text.setCharacterSize(60);
	m_text.setString("Music By:");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 70;
	m_text.setCharacterSize(50);
	m_text.setString("Martin Koniar");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	// SHADOW

	m_text.setColor(sf::Color(156, 55, 6, 255));

	position = renderer.getView().getCenter() + sf::Vector2f(0, -renderer.getView().getSize().y / 6.0f - 20);
	m_text.setCharacterSize(100);
	m_text.setString("Credits");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 150;
	m_text.setCharacterSize(60);
	m_text.setString("Game By:");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 70;
	m_text.setCharacterSize(50);
	m_text.setString("Jan Ivanecky");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 70;
	m_text.setCharacterSize(50);
	m_text.setString("Michal Ivanecky");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 100;
	m_text.setCharacterSize(60);
	m_text.setString("Music By:");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

	position.y += 70;
	m_text.setCharacterSize(50);
	m_text.setString("Martin Koniar");
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(position);
	renderer.draw(m_text);

}

void CreditScreen::Pressed(const sf::Keyboard::Key key)
{

}

const bool CreditScreen::IsReadyForChange()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
}

std::shared_ptr<Screen> CreditScreen::GetNextScreen()
{
	return Screen::NewMenuScreen();
}