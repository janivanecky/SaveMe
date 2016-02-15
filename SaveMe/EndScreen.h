#pragma once
#include "Screen.h"
#include "ScoreManager.h"

class EndScreen: public Screen
{
public:
	EndScreen(const int numberOfSurvivorSaved);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	const bool IsReadyForChange();
	const bool IsOverriding(){ return false; };
	void Pressed(const sf::Keyboard::Key key);
	std::shared_ptr<Screen> GetNextScreen();
private:
	sf::Text m_text;
	sf::Font m_font;

	int m_survivorsSaved;

	bool m_isNewHighScore;

	float m_time;
};