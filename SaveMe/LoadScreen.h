#pragma once
#include "Screen.h"

class LoadScreen : public Screen
{
public:
	LoadScreen();
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	const bool IsReadyForChange(){ return true; };
private:
	sf::Text m_text;
	sf::Font m_font;
	sf::Sprite m_bg;
};