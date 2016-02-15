#pragma once

#include "Screen.h"

class StoryScreen : public Screen
{
public:
	StoryScreen();
	void Draw(sf::RenderWindow& renderer);
	const bool IsReadyForChange();
	std::shared_ptr<Screen> GetNextScreen();
	void Pressed(const sf::Keyboard::Key key);
private:
	sf::Text m_text;
	bool m_isReadyForChange;
};