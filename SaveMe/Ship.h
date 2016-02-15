#pragma once

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Animator.h"
#include "ParticleSystem.h"
#include "Math.h"
#include "Survivor.h"
#include "Camera.h"

class Ship
{
public:
	Ship();
	void UpdateControls(const float dt);
	void Update(const float dt);
	void Draw(sf::RenderWindow& renderer);
	void DrawMini(sf::RenderWindow& renderer);
	void Save(const Survivor& survivor);
	void Save();
	void Lower();
	const sf::Vector2f& GetPosition();
	const float GetFuel();
	void RefillFuel();
	void UnloadPassangers();
	const int GetNumberOfPassengers();
	const int GetMaxCapacity();
	const float GetSpeed1();
	float m_rotation;
private:
	Animator m_animator;
	Animator m_shadow;
	ParticleSystem m_particles;
	sf::Vector2f m_position;

	float m_speed;
	sf::Vector2f m_velocity;

	int m_capacity;
	float m_orientation;

	float m_fuel;
	float m_distanceTraveled;

	float m_scale;

	float m_refillTime;

	float m_saveTime;

	sf::SoundBuffer m_engine;
	sf::SoundBuffer m_passangerTakenSound;
	sf::Sound m_sound;
	sf::Sound m_sound2;

	float m_speed1;

	sf::Sprite m_cross;

	float m_leftTurnTime;
	float m_rightTurnTime;
};