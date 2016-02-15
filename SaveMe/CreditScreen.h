#pragma once

#include "Screen.h"

class CreditScreen: public Screen
{
public:
	CreditScreen();
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void Pressed(const sf::Keyboard::Key key);
	const bool IsReadyForChange();
	std::shared_ptr<Screen> GetNextScreen();
private:
	sf::Text m_text;
	sf::Font m_font;
	sf::Sprite m_bg;
};