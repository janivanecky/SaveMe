#include "ParticleSystem.h"

float getLifetimeFromEffect(const ParticleEffect effect)
{
	float lifetime = 0;
	switch (effect)
	{
	case FIRE:
		lifetime = FIRE_PARTICLE_LIFETIME;
		break;
	case SMOKE:
		lifetime = SMOKE_PARTICLE_LIFETIME;
		break;
	}

	return lifetime;
}

float getStartOpacityFromEffect(const ParticleEffect effect)
{
	float opacity;
	switch (effect)
	{
	case FIRE:
		opacity = 1;
		break;
	case SMOKE:
		opacity = 0.3f;
		break;
	}
	return opacity;
}

const sf::Color getFireColor()
{
	int randomColor = rand() % 3;
	sf::Color color = sf::Color(255, 78, 0);
	if (randomColor == 1)
		color = sf::Color(255, 24, 0);
	else if (randomColor == 2)
		color = sf::Color(255, 160, 0);
	return color;
}

const int getParticleCountByEffect(const ParticleEffect effect)
{
	int particleCount = 0;
	switch (effect)
	{
	case FIRE:
		particleCount = 100;
		break;
	case SMOKE:
		particleCount = 5;
		break;
	}

	return particleCount;
}

const sf::Color getSmokeColor()
{
	int randomColor = rand() % 115;
	sf::Color color = sf::Color(randomColor, randomColor, randomColor);
	return color;
}

const sf::Color ParticleSystem::getColorByEffect(const ParticleEffect effect)
{
	sf::Color color;
	switch (effect)
	{
	case FIRE:
		color = getFireColor();
		break;
	case SMOKE:
		color = getSmokeColor();
		break;
	}
	return color;
}

const sf::Vector2f GetSizeByEffect(const ParticleEffect effect)
{
	int size = 0;
	switch (effect)
	{
	case FIRE:
		size = 4;
		break;
	case SMOKE:
		size = 20;
		break;
	}
	return sf::Vector2f(size, size);
}

const sf::Vector2f ParticleSystem::getOffsetByEffect(const ParticleEffect effect)
{
	sf::Vector2f returnOffset(0, 0);
	switch (effect)
	{
	case FIRE:
		returnOffset = sf::Vector2f(rand() % 80 - 40, rand() % 80 - 40);
		break;
	case SMOKE:
		int offsetX = rand() % 100 + 200;
		int offsetY = rand() % 100 + 100;
		float randomX = -rand() % (offsetX / 4) - 3 * offsetX / 4.0f;
		float offsetXSquared = offsetX * offsetX;
		float offsetYSquared = offsetY * offsetY;
		float randomXSquared = randomX * randomX;
		float yPossible = sqrt((offsetXSquared * offsetYSquared - randomXSquared * offsetYSquared) / offsetXSquared);
		float randomY = rand() % (2 * (int)yPossible) - yPossible + 0.5f;
		returnOffset = sf::Vector2f(randomX, randomY);
		break;
	}

	return returnOffset;
}

ParticleSystem::ParticleSystem(const std::string image, float cadence, const sf::Vector2f& position, const ParticleEffect effectType) :
m_nextParticle(0),
m_cadence(cadence),
m_position(position),
m_scale(1),
m_duration(0),
m_shape(),
m_effect(effectType),
m_particleLifetime(getLifetimeFromEffect(m_effect)),
m_isDisabled(false),
m_fireUpDuration(0)
{
	m_shape.setSize(GetSizeByEffect(m_effect));
	m_shape.setOrigin(GetSizeByEffect(m_effect) / 2.0f);
}

void ParticleSystem::Update(const float dt, const sf::Vector2f& offset)
{
	if (!m_isDisabled)
	{
		auto i = std::begin(m_particles);
		while (i != std::end(m_particles))
		{
			(*i)->life -= dt;
			(*i)->opacity -= getStartOpacityFromEffect(m_effect) * dt / m_particleLifetime;
			(*i)->position += ((*i)->target - (*i)->originalPosition) * (dt / m_particleLifetime);

			if ((*i)->life <= 0)
			{
				delete *i;
				i = m_particles.erase(i);
			}
			else
				i++;
		}

		if (m_fireUpDuration > 0)
			m_fireUpDuration -= dt;

		if (m_cadence > 0 && m_duration > 0)
		{
			m_nextParticle -= dt;
			m_duration -= dt;
			if (m_nextParticle <= 0)
			{
				m_nextParticle = m_cadence;
				for (int i = 0; i < getParticleCountByEffect(m_effect); i++)
					emit(m_position + offset);
			}
		}
	}	

}

void ParticleSystem::emit(const sf::Vector2f& position)
{
	float scale = (rand() / (RAND_MAX)) + 1.0f;

	sf::Vector2f offset = getOffsetByEffect(m_effect);
	sf::Color color = getColorByEffect(m_effect);
	if (m_fireUpDuration > 0)
		color = sf::Color::Blue;
	float opacity = getStartOpacityFromEffect(m_effect);
	sf::Vector2f spawnOffset(0, 0);
	if (m_effect == SMOKE)
		spawnOffset = sf::Vector2f(rand() % 20 - 10, rand() % 20 - 10);

	Particle *p = new Particle(position + spawnOffset, scale, color, position + offset, m_particleLifetime, opacity);
	m_particles.insert(m_particles.begin(), p);
} 

void ParticleSystem::Draw(sf::RenderWindow& renderer)
{
	if (!m_isDisabled)
	{
		for (auto p : m_particles)
		{
			sf::Color color = p->color;
			color.a = p->opacity * 255;
			m_shape.setPosition(p->position);
			m_shape.setScale(p->size, p->size);
			m_shape.setFillColor(color);
			renderer.draw(m_shape);
		}
	}
}

void ParticleSystem::FireUp()
{
	m_fireUpDuration = 1.0f;
}

void ParticleSystem::Emit()
{
	m_duration = 0.3f;
}

void ParticleSystem::Disable()
{
	m_isDisabled = true;
}