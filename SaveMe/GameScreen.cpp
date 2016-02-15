#include "GameScreen.h"
#include <sstream>

GameScreen::GameScreen() :
m_ship(),
m_survivors(),
m_environment(),
m_buildings(),
m_fuelTanks(),
m_camera(),
m_base(),
m_timer(120),
m_font(AssetManager::GetInstance().GetFont("Assets/joystix monospace.ttf")),
m_text(),
m_saveCounter(0),
m_rotation(0),
m_fpsView(false),
m_isPanskyRezim(true),
m_isUnlimitedFuel(false),
m_fuelBuffer(),
m_fuelSound(),
m_smoke("particle", 0.03f, m_ship.GetPosition(), SMOKE),
m_isReadyForPause(),
m_isReadyToEnd(false),
m_hasEnded(false)
{
	srand(time(NULL));

	int initialSpawn = 100;
	float spawnAddition = initialSpawn * (2 / 3);

	m_text.setFont(m_font);
	m_text.setColor(sf::Color(255, 255, 255, 255));
	m_text.setCharacterSize(20);
	
	// Spawn Environment
	for (int i = 0; i < 800; i++)
	{
		sf::Vector2f randomPosition(rand() % (int)DISPLAY_RESX * 10 - DISPLAY_RESX * 5,
			rand() % (int)DISPLAY_RESY * 10 - DISPLAY_RESY * 5);

		while (m_environment.IsNear(randomPosition, 100))
		{
			randomPosition = sf::Vector2f(rand() % (int)DISPLAY_RESX * 10 - DISPLAY_RESX * 5,
				rand() % (int)DISPLAY_RESY * 10 - DISPLAY_RESY * 5);
		}

		Environment *newEnvironment = new Environment(randomPosition, "crater");
		m_environment.Insert(*newEnvironment);
	}

	spawnEnvironment();

	m_camera.setCenter(0, 0);
	m_camera.setSize(DISPLAY_RESX * 1.0f, DISPLAY_RESY * 1.0f);

	m_save.loadFromFile("Assets/save.ogg");
	m_sound.setBuffer(m_save);

	m_fuelBuffer.loadFromFile("Assets/fuel.ogg");
	m_fuelSound.setBuffer(m_fuelBuffer);
}

void GameScreen::Update(const float dt)
{
	for (int i = 0; i < m_survivors.size();)
	{
		m_survivors[i]->Update(dt);
		if (m_fpsView)
		{
			if (m_ship.m_rotation + 90 < 180 || m_rotation > 90)
				m_rotation += ((m_ship.m_rotation + 90) - m_rotation) / 1000.0f;
			else
				m_rotation -= ((-m_ship.m_rotation - 90) - m_rotation) / 1000.0f;

		}
		else
			m_rotation += (0 - m_rotation) / 1000.0f;

		m_survivors[i]->SetRotation(m_rotation);
		if (m_survivors[i]->IsSaved())
		{
			float dx = m_ship.GetPosition().x - m_survivors[i]->GetPosition().x;
			float dy = m_ship.GetPosition().y - m_survivors[i]->GetPosition().y;
			float distance = dx * dx + dy * dy;
			if (distance < 2500)
			{
				m_survivors.erase(m_survivors.begin() + i);
				continue;
			}
		}
		i++;
	}

	m_smoke.Update(dt);
	m_smoke.Emit();
	m_fuelTanks.Rotate(m_rotation);
	m_fuelTanks.Update(dt);
	m_buildings.Update(dt);
	
	if (m_isUnlimitedFuel || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && getLengthSquared(m_ship.GetPosition()) < 225 * 225))
		m_ship.RefillFuel();

	if (m_isPanskyRezim)
	{
		std::vector<std::shared_ptr<Survivor>>::const_iterator index = CheckIfNearby(m_ship.GetPosition(), m_survivors, 100);
		if (index != m_survivors.end())
		{
			m_ship.Save(*index->get());
		}
		else
		{
			if (getLengthSquared(m_ship.GetPosition()) < 225 * 225 && m_ship.GetNumberOfPassengers() > 0)
			{
				m_saveCounter += m_ship.GetNumberOfPassengers();
				m_ship.UnloadPassangers();
				m_sound.play();
			}
		}
	}
	if (!IsReadyForChange() && m_fuelTanks.IsNear(m_ship.GetPosition(), 100))
	{
		m_fuelTanks.EraseNearest(m_ship.GetPosition(), 100);
		m_ship.RefillFuel();
		m_fuelSound.play();
	}
	
	if (!m_hasEnded && (m_ship.GetFuel() == 0 || m_timer <= 0))
	{
		m_hasEnded = true;
		m_isReadyToEnd = true;
	}
	if (!m_hasEnded)
	{
		m_timer -= dt;
		m_ship.UpdateControls(dt);
	}
	m_ship.Update(dt);
	m_base.Update(dt);

	m_camera.setCenter(m_ship.GetPosition());
	Camera::GetInstance().Update(m_ship.GetPosition());
	m_camera.setCenter(Camera::GetInstance().GetPosition());
}


void GameScreen::Draw(sf::RenderWindow& renderer)
{
	m_camera.setRotation(m_rotation);
	renderer.setView(m_camera);

	m_environment.Draw(renderer);
	m_fuelTanks.Draw(renderer);	

	m_base.Draw(renderer);
	//m_smoke.Draw(renderer);
	for (auto survivor : m_survivors)
	{
		survivor->Draw(renderer);
	}
	m_buildings.Draw(renderer);
	m_ship.Draw(renderer);

	sf::View minimap;
	minimap.setViewport(sf::FloatRect(0, 0.75, 0.25 , 0.25));
	minimap.setCenter(m_ship.GetPosition());
	minimap.setSize(DISPLAY_RESX * 10, DISPLAY_RESY * 10);
	minimap.setRotation(m_rotation);
	renderer.setView(minimap);
	
	sf::RectangleShape bg;
	bg.setFillColor(sf::Color(0, 0, 0, 100));
	bg.setOrigin(sf::Vector2f(DISPLAY_RESX * 30, DISPLAY_RESY * 30));
	bg.setSize(sf::Vector2f(DISPLAY_RESX * 60, DISPLAY_RESY * 60));
	renderer.draw(bg);

	sf::FloatRect viewPort = sf::FloatRect(renderer.getView().getCenter() - renderer.getView().getSize(),
		renderer.getView().getSize() * 1.5f);
	for (auto survivor : m_survivors)
	{
		if (viewPort.contains(survivor->GetPosition()))
			survivor->DrawMini(renderer);
	}

	m_fuelTanks.DrawMini(renderer);
	m_base.DrawMini(renderer);
	m_ship.DrawMini(renderer);

	renderer.setView(renderer.getDefaultView());
	m_text.setColor(sf::Color::White);

	m_text.setCharacterSize(20);
	std::stringstream ss2;
	ss2 << "Survivors saved: " << m_saveCounter;
	m_text.setString(ss2.str());
	m_text.setPosition(renderer.getSize().x * 0.25 + 20, renderer.getSize().y - 50 - 40 - m_text.getLocalBounds().height);
	renderer.draw(m_text);
	std::stringstream ss;
	int seconds = (int)m_timer % 60;
	std::string potentialZero = seconds < 10 ? "0" : "";
	ss << (int)m_timer / 60 << ":" << potentialZero << seconds;
	m_text.setCharacterSize(80);
	m_text.setString(ss.str());
	m_text.setPosition(renderer.getSize().x * 0.25 + 20 + 300 + 20, renderer.getSize().y - 80 - 20.0f);
	renderer.draw(m_text);
	m_text.setCharacterSize(20);

	sf::RectangleShape passenger;
	passenger.setFillColor(sf::Color(100,100,100,255));
	passenger.setSize(sf::Vector2f(25, 50));
	int capacity = m_ship.GetMaxCapacity();
	for (int i = 0; i < capacity; i++)
	{
		passenger.setPosition(renderer.getSize().x * 0.25 + 20 + i * 30, renderer.getSize().y - 50 - 20);
		renderer.draw(passenger);
	}

	int passengerCount = m_ship.GetNumberOfPassengers();
	passenger.setFillColor(sf::Color::White);
	for (int i = 0; i < passengerCount; i++)
	{
		passenger.setPosition(renderer.getSize().x * 0.25 + 20 + i * 30, renderer.getSize().y - 50 - 20);
		renderer.draw(passenger);
	}

	sf::Color fuelColor = sf::Color::White;
	if (m_ship.GetFuel() < LOW_FUEL_TRESHOLD)
	{
		fuelColor = sf::Color::Red;
		if (cos(m_timer * 10) < 0)
			fuelColor = sf::Color::Transparent;
	}

	sf::RectangleShape fuelTank;
	fuelTank.setFillColor(fuelColor);
	fuelTank.setSize(sf::Vector2f(50, 100));
	fuelTank.setPosition(renderer.getSize().x - 120, renderer.getSize().y - 20);
	fuelTank.setOrigin(0, fuelTank.getLocalBounds().height);
	fuelTank.setScale(1, m_ship.GetFuel());
	renderer.draw(fuelTank);

	sf::RectangleShape fuelTankBorder;
	fuelTankBorder.setOutlineColor(fuelColor);
	fuelTankBorder.setOutlineThickness(5);
	fuelTankBorder.setFillColor(sf::Color::Transparent);
	fuelTankBorder.setSize(sf::Vector2f(60, 110));
	fuelTankBorder.setPosition(renderer.getSize().x - 125, renderer.getSize().y - 15 - 110);
	renderer.draw(fuelTankBorder);
	
	m_text.setString("fuel");
	m_text.setColor(fuelColor);
	m_text.setCharacterSize(15);
	m_text.setPosition(renderer.getSize().x - 120, renderer.getSize().y - 150);
	renderer.draw(m_text);

	m_text.setString(toString((int)(m_ship.GetFuel() * 100)) + std::string("%"));
	m_text.setCharacterSize(10);
	m_text.setOrigin(0, m_text.getLocalBounds().height / 2);
	m_text.setPosition(renderer.getSize().x - 50, renderer.getSize().y - 20 - m_ship.GetFuel() * 100);
	renderer.draw(m_text);

	m_text.setColor(sf::Color::White);

	if (m_fpsView)
	{
		m_text.setString("Pilot view ON");
		m_text.setCharacterSize(20);
		m_text.setPosition(renderer.getSize().x - m_text.getLocalBounds().width - 20, 20);
		renderer.draw(m_text);
	}

	if (m_isUnlimitedFuel)
	{
		m_text.setString("Unlimited Fuel ON");
		m_text.setCharacterSize(20);
		m_text.setPosition(renderer.getSize().x - m_text.getLocalBounds().width - 20, renderer.getSize().y - m_text.getLocalBounds().height - 20);
		renderer.draw(m_text);
	}
/*
	m_text.setString(toString(m_ship.GetSpeed1()));
	m_text.setCharacterSize(10);
	m_text.setPosition(10, 10);
	renderer.draw(m_text);*/

	if (m_ship.GetFuel() < LOW_FUEL_TRESHOLD)
	{
		m_text.setString("FUEL LOW");
		m_text.setCharacterSize(40);
		m_text.setColor(fuelColor);
		m_text.setPosition(renderer.getView().getCenter().x - m_text.getLocalBounds().width / 2, 50);
		renderer.draw(m_text);
	}
	if (m_ship.GetNumberOfPassengers() == 10)
	{
		sf::Color capacityColor = sf::Color::Green;
		if (cos(m_timer * 10) < 0)
			capacityColor = sf::Color::Transparent;
		m_text.setString("SHIP FULL - RETURN TO BASE");
		m_text.setCharacterSize(40);
		m_text.setColor(capacityColor);
		m_text.setPosition(renderer.getView().getCenter().x - m_text.getLocalBounds().width / 2, 100);
		renderer.draw(m_text);
	}


}

void GameScreen::Pressed(const sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Key::Tab)
	{
		m_fpsView = !m_fpsView;
	}
	else if (key == sf::Keyboard::Key::F1)
	{
		//m_isPanskyRezim = !m_isPanskyRezim;
	}
	else if (key == sf::Keyboard::Key::F2)
	{
		//m_isUnlimitedFuel = !m_isUnlimitedFuel;
	}
	else if (key == sf::Keyboard::Key::Escape)
	{
		m_isReadyForPause = true;
	}
	/*if (key == sf::Keyboard::Key::Space)
	{
		std::vector<std::shared_ptr<Survivor>>::const_iterator index = CheckIfNearby(m_ship.GetPosition(), m_survivors, 100);
		if (index != m_survivors.end())
		{
			m_ship.Save(*index->get());
		}
		else
		{
			if (getLengthSquared(m_ship.GetPosition()) < 225 * 225)
			{
				m_saveCounter += m_ship.GetNumberOfPassengers();
				m_ship.UnloadPassangers();
				m_sound.play();
			}
			m_ship.Save();
		}
	}*/
}

const bool GameScreen::IsReadyForChange()
{
	return m_isReadyToEnd || m_isReadyForPause;
}

std::shared_ptr<Screen> GameScreen::GetNextScreen()
{
	if (m_isReadyForPause)
	{
		m_isReadyForPause = false;
		return Screen::NewPauseScreen(this->shared_from_this());
	}
	else
	{
		m_isReadyToEnd = false;
		return Screen::NewEndScreen(m_saveCounter);
	}
}

void GameScreen::spawnEnvironment()
{
	int initialSpawn = 3;
	float spawnAddition = initialSpawn * 2;
	for (int i = 0; i < 8; i++)
	{
		int currentSpawnCount = initialSpawn + i * spawnAddition;
		for (int j = 0; j < currentSpawnCount; j++)
		{
			float radiusMin = 600 + i * 600;
			float spawnRadius = rand() % 600 + radiusMin;
			float spawnAngle = degreesToRadians(rand() % 180) + i > currentSpawnCount / 2 ? 180: 0;
			sf::Vector2f spawnPosition(cos(spawnAngle) * spawnRadius, sin(spawnAngle) * spawnRadius);
			while (m_buildings.IsNear(spawnPosition,500))
			{
				float spawnRadius = rand() % 600 + radiusMin;
				float spawnAngle = degreesToRadians(rand() % 360);
				spawnPosition = sf::Vector2f(cos(spawnAngle) * spawnRadius, sin(spawnAngle) * spawnRadius);
			}
			
			int randomEnvironment = rand() % 7; 
			if (randomEnvironment > 0)
			{
				Building *newBuilding = new Building(spawnPosition);
				m_buildings.Insert(*newBuilding);

				std::vector<std::shared_ptr<Survivor>> survivorsToSpawn;
				for (int j = 0; j < newBuilding->GetSurvivorCount(); j++)
				{
					float radiusMin = newBuilding->GetSurvivorDistance();
					float spawnRadius = rand() % 200 + radiusMin;
					float spawnAngle = degreesToRadians(rand() % 360);
					sf::Vector2f survivorPosition(cos(spawnAngle) * spawnRadius, sin(spawnAngle) * spawnRadius);
					survivorPosition += spawnPosition;
					while (CheckIfNearby(survivorPosition, survivorsToSpawn, 100) != survivorsToSpawn.end())
					{
						float spawnRadius = rand() % 200 + radiusMin;
						float spawnAngle = degreesToRadians(rand() % 360);
						survivorPosition = spawnPosition + sf::Vector2f(cos(spawnAngle) * spawnRadius, sin(spawnAngle) * spawnRadius);
					}
					std::shared_ptr<Survivor> newSurvivor = std::shared_ptr<Survivor>(new Survivor(survivorPosition));
					survivorsToSpawn.push_back(newSurvivor);
					m_survivors.push_back(newSurvivor);
				}
			}
			else
			{
				m_fuelTanks.Insert(*new Fuel(spawnPosition));
			}
			
		}
	}
}

const bool GameScreen::IsNextScreenOverriding()
{
	return false;
}