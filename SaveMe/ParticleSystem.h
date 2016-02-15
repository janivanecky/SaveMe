#pragma once
#include "SFML\Graphics.hpp"
#include "Config.h"
#include <memory>

enum ParticleEffect
{
	FIRE,
	SMOKE
};

struct Particle
{
	sf::Vector2f position;
	sf::Vector2f target;
	sf::Vector2f originalPosition;
	float size;
	float life;
	float opacity;
	sf::Color color;
	Particle(sf::Vector2f position, float size, sf::Color color, sf::Vector2f target, float lifeTime, float startOpacity)
	{
		this->position = position;
		originalPosition = position;
		this->size = size;
		this->opacity = startOpacity;
		life = lifeTime;
		this->color = color;
		this->target = target;
	}
};

class ParticleSystem
{
public:
	ParticleSystem(const std::string type, float cadence, const sf::Vector2f& position, const ParticleEffect effectType);
	void Update(const float dt, const sf::Vector2f& offset = sf::Vector2f(0, 0));
	void Draw(sf::RenderWindow& renderer);
	void Emit();
	void Disable();
	void FireUp();
private:
	bool m_isDisabled;
	sf::RectangleShape m_shape;

	std::vector<Particle *> m_particles;

	float m_nextParticle;
	float m_cadence;
	float m_scale;
	float m_fireUpDuration;
	const sf::Vector2f& m_position;
	ParticleEffect m_effect;

	float m_particleLifetime;

	float m_duration;
	void emit(const sf::Vector2f& position);

	const sf::Color getColorByEffect(const ParticleEffect effect);
	const sf::Vector2f getOffsetByEffect(const ParticleEffect effect);
};