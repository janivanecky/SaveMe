#pragma once

#include "Screen.h"

class PauseScreen : public Screen
{
public:
	PauseScreen(std::shared_ptr<Screen> pausedScreen);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void Pressed(const sf::Keyboard::Key key);
	const bool IsOverriding() { return false; };
	const bool IsReadyForChange();
	std::shared_ptr<Screen> GetNextScreen();
	const bool IsPausing(){ return true; };
private:
	sf::Text m_text;
	sf::Font m_font;

	int m_selectedItem;

	bool m_isReadyForUnpause;

	std::shared_ptr<Screen> m_pausedScreen;
};