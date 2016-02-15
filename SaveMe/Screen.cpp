#include "Screen.h"
#include "GameScreen.h"
#include "EndScreen.h"
#include "MenuScreen.h"
#include "LoadScreen.h"
#include "CreditScreen.h"
#include "ExitScreen.h"
#include "PauseScreen.h"
#include "ScoreScreen.h"
#include "StoryScreen.h"

std::shared_ptr<Screen> Screen::NewGameScreen()
{
	return std::shared_ptr<Screen>(new GameScreen());
}

std::shared_ptr<Screen> Screen::NewEndScreen(const int numberOfSurvivorsSaved)
{
	return std::shared_ptr<Screen>(new EndScreen(numberOfSurvivorsSaved));
}

std::shared_ptr<Screen> Screen::NewMenuScreen()
{
	return std::shared_ptr<Screen>(new MenuScreen());
}

std::shared_ptr<Screen> Screen::NewLoadScreen()
{
	return std::shared_ptr<Screen>(new LoadScreen());
}

std::shared_ptr<Screen> Screen::NewCreditScreen()
{
	return std::shared_ptr<Screen>(new CreditScreen());
}

std::shared_ptr<Screen> Screen::NewPauseScreen(std::shared_ptr<Screen> pauseScreen)
{
	return std::shared_ptr<Screen>(new PauseScreen(pauseScreen));
}

std::shared_ptr<Screen> Screen::NewScoreScreen()
{
	return std::shared_ptr<Screen>(new ScoreScreen());
}

std::shared_ptr<Screen> Screen::NewExitScreen()
{
	return std::shared_ptr<Screen>(new ExitScreen());
}

std::shared_ptr<Screen> Screen::NewStoryScreen()
{
	return std::shared_ptr<Screen>(new StoryScreen());
}