#pragma once

#include "Screen.h"
#include "ScoreManager.h"

class ScoreScreen : public Screen
{
public:
	ScoreScreen();
	void Draw(sf::RenderWindow& renderer);
	void Pressed(const sf::Keyboard::Key key);
	const bool IsReadyForChange();
	std::shared_ptr<Screen> GetNextScreen();
private:
	std::vector<int> m_scores;
	sf::Sprite m_bg;

	sf::Text m_text;
};