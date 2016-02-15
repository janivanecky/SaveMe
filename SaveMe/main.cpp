#include <SFML/Graphics.hpp> 
#include <memory>
#include "Screen.h"
#include "Time.h"
#include "AssetManager.h"
#include "SFML\Audio.hpp"
#include <Windows.h>


int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::vector< sf::VideoMode > modes = sf::VideoMode::getFullscreenModes();
	SetDisplayResolution(modes.begin()->width, modes.begin()->height);
	//sf::RenderWindow window(sf::VideoMode(DISPLAY_RESX, DISPLAY_RESY), "Save Me", sf::Style::Fullscreen);
	sf::RenderWindow window(sf::VideoMode((int)(DISPLAY_RESX * 0.8f), (int)(DISPLAY_RESY * 0.8f)), "Save Me");
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);

	std::shared_ptr<Screen> currentScreen(Screen::NewStoryScreen());
	std::shared_ptr<Screen> overlayScreen;
	

	sf::Music m_music;
	if (!m_music.openFromFile("Assets/saveme.ogg"))
	{
		float x = 120;
	}
	m_music.play();
	m_music.setLoop(true);
	m_music.setVolume(60);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)// || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)))
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (!overlayScreen)// || (overlayScreen && !overlayScreen->IsPausing()))
					currentScreen->Pressed(event.key.code);
				if (overlayScreen)
					overlayScreen->Pressed(event.key.code);
			}
		}

		Time::GetInstance().Update();
		window.clear(sf::Color(82, 0, 0));

		float delta = Time::GetInstance().GetDelta();
		while (delta)
		{
			if (!overlayScreen || (overlayScreen && !overlayScreen->IsPausing()))
				currentScreen->Update(delta);
			if (overlayScreen)
				overlayScreen->Update(delta);
			delta = Time::GetInstance().GetDelta();
		}

		currentScreen->Draw(window);
		if (overlayScreen)
			overlayScreen->Draw(window);

		if(currentScreen->IsReadyForChange())
		{
			if (currentScreen->IsNextScreenOverriding())
			{
				window.clear(sf::Color(82, 0, 0));
				std::shared_ptr<Screen> loadScreen = Screen::NewLoadScreen();
				loadScreen->Draw(window);
				window.display();
			}

			std::shared_ptr<Screen> newScreen = currentScreen->GetNextScreen();
			if (newScreen->IsOverriding())
			{
				currentScreen = newScreen;
				overlayScreen.reset();
			}
			else
			{
				overlayScreen = newScreen;
			}
		}
		if (overlayScreen && overlayScreen->IsReadyForChange())
		{
			std::shared_ptr<Screen> newScreen = overlayScreen->GetNextScreen();
			if (newScreen->IsOverriding())
			{
				currentScreen = newScreen;
				overlayScreen.reset();
			}
			else
				overlayScreen = newScreen;
		}


		if (currentScreen->IsExit())
			window.close();
		
		window.display();
	}

	
	return 0;
}