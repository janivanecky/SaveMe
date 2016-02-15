#pragma once

#include "SFML\Graphics.hpp"
#include "Config.h"
#include <memory>
#include "AssetManager.h"
#include "Tools.h"

class Screen
{
public:
	Screen(){};
	virtual void Update(const float dt){};
	virtual void Draw(sf::RenderWindow& renderer){};
	virtual void Pressed(const sf::Keyboard::Key key){};
	virtual const bool IsReadyForChange(){ return true; };
	virtual std::shared_ptr<Screen> GetNextScreen(){ return Screen::NewGameScreen(); };
	virtual const bool IsOverriding(){ return true; };
	virtual const bool IsNextScreenOverriding(){ return true; };
	virtual const bool IsExit(){return false;};
	virtual const bool IsPausing(){ return false; };

	static std::shared_ptr<Screen> NewGameScreen();
	static std::shared_ptr<Screen> NewEndScreen(const int numberOfSurvivorsSaved);
	static std::shared_ptr<Screen> NewMenuScreen();
	static std::shared_ptr<Screen> NewLoadScreen();
	static std::shared_ptr<Screen> NewCreditScreen();
	static std::shared_ptr<Screen> NewPauseScreen(std::shared_ptr<Screen> pauseScreen);
	static std::shared_ptr<Screen> NewExitScreen();
	static std::shared_ptr<Screen> NewScoreScreen();
	static std::shared_ptr<Screen> NewStoryScreen();
};