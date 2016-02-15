#pragma once
#include "Screen.h"
#include "Ship.h"
#include "Survivor.h"
#include "Drawable.h"
#include "Enviroment.h"
#include <time.h>
#include <memory>
#include "Base.h"
#include "QuadTree.h"
#include "Building.h"
#include "Math.h"
#include "Worm.h"
#include "Camera.h"
#include "Fuel.h"

class GameScreen : public Screen, public std::enable_shared_from_this<Screen>
{
public:
	GameScreen();
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void Pressed(const sf::Keyboard::Key key);
	const bool IsReadyForChange();
	std::shared_ptr<Screen> GetNextScreen();
	const bool IsNextScreenOverriding();
private:
	Ship m_ship;
	std::vector<std::shared_ptr<Survivor>> m_survivors;
	QuadTree m_environment;
	QuadTree m_buildings;
	QuadTree m_fuelTanks;
	Base m_base;

	ParticleSystem m_smoke;

	float m_timer;
	int m_saveCounter;

	sf::Text m_text;
	sf::Font m_font;

	float m_rotation;

	bool m_fpsView;
	bool m_isPanskyRezim;
	bool m_isUnlimitedFuel;

	sf::Sound m_sound;
	sf::SoundBuffer m_save;
	sf::Sound m_fuelSound;
	sf::SoundBuffer m_fuelBuffer;

	void spawnEnvironment();

	sf::View m_camera;

	bool m_isReadyForPause;
	bool m_isReadyToEnd;
	bool m_hasEnded;
};




