#pragma once
#include "Screen.h"
#include <functional>
#include "ScoreManager.h"

class MenuScreen: public Screen
{
public:
	MenuScreen();
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer); 
	void Pressed(const sf::Keyboard::Key key);
	const bool IsReadyForChange();
	std::shared_ptr<Screen> GetNextScreen();
private:
	sf::Text m_text;
	sf::Font m_font;

	int m_selectedItem;

	sf::Sprite m_bg;

	bool m_isReadyForChange;

	int m_highscore;
};