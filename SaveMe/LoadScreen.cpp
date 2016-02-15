#include "LoadScreen.h"

LoadScreen::LoadScreen() :
m_font(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf")),
m_text(),
m_bg()
{
	m_text.setFont(m_font);
	m_text.setColor(sf::Color(255, 255, 255, 255));
	m_text.setCharacterSize(100);

	m_bg.setTexture(AssetManager::GetInstance().GetTexture("Assets/bg.jpg"));
	m_bg.setOrigin(m_bg.getTextureRect().width / 2, m_bg.getTextureRect().height / 2);
}

void LoadScreen::Update(const float dt)
{

}

void LoadScreen::Draw(sf::RenderWindow& renderer)
{
	sf::View bgView;
	bgView.setSize(m_bg.getTextureRect().width, m_bg.getTextureRect().height);
	renderer.setView(bgView);
	m_bg.setPosition(renderer.getView().getCenter());
	renderer.draw(m_bg);

	m_text.setCharacterSize(60);

	m_text.setColor(sf::Color(0, 0, 0, 200));
	m_text.setString("LOADING...");
	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, 0);
	m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, 60));
	renderer.draw(m_text);

	m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, 0);
	m_text.setPosition(renderer.getView().getCenter() + sf::Vector2f(0, 50));
	m_text.setColor(sf::Color::White);
	renderer.draw(m_text);
}