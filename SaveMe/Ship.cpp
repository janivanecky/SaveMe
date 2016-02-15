#include "Ship.h"

Ship::Ship() :
m_animator(),
m_position(),
m_velocity(),
m_rotation(),
m_capacity(10),
m_fuel(1),
m_distanceTraveled(0),
m_speed(0),
m_shadow(),
m_particles("particle", 0.0333f, m_position, FIRE),
m_scale(0.15f),
m_refillTime(0),
m_saveTime(0),
m_engine(),
m_passangerTakenSound(),
m_sound(),
m_speed1(0.05f),
m_orientation(1),
m_leftTurnTime(0),
m_rightTurnTime(0),
m_cross()
{
	m_animator.AddAnimation("move", "Assets/ship.png", 2, 1.0f, true);
	m_animator.AddAnimation("sidemove", "Assets/vehicleside.png", 2, 1.0f, true);
	m_animator.AddAnimation("sidemoveX", "Assets/vehiclesideex.png", 2, 1.0f, true);
	m_animator.SetAnimation("move");

	m_shadow.AddAnimation("shadow", "Assets/shadow.png", 1, 1.0f, true);
	m_shadow.SetAnimation("shadow");

	m_cross.setTexture(AssetManager::GetInstance().GetTexture("Assets/cross.png"));

	if (!m_passangerTakenSound.loadFromFile("Assets/passenger.wav"))
	{
		float x = 0;
	}
	m_engine.loadFromFile("Assets/engine.ogg");
	
	m_sound.setVolume(15);
	m_sound.setLoop(true);
	m_sound.setBuffer(m_engine);

	m_sound2.setBuffer(m_passangerTakenSound);
}

void Ship::UpdateControls(const float dt)
{
	float speed = dt / 0.0333f;
/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageDown))
	{
		m_speed1 -= 0.005f * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::PageUp))
	{
		m_speed1 += 0.005f * speed;
	}*/
	m_animator.SetAnimation("move");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_rotation -= 4.0f * speed;// / (sqrt(getLengthSquared(m_velocity)) / 15.0f);// 2.0f;
		if (m_leftTurnTime < 0.15f)
			m_animator.SetAnimation("sidemove");
		else
			m_animator.SetAnimation("sidemoveX");
		m_orientation = -1;
		m_leftTurnTime += dt;
	}
	else
		m_leftTurnTime = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_rotation += 4.0f * speed;// / (sqrt(getLengthSquared(m_velocity)) / 15.0f);//2.0f;
		if (m_rightTurnTime < 0.15f)
			m_animator.SetAnimation("sidemove");
		else
			m_animator.SetAnimation("sidemoveX");
		m_orientation = 1;
		m_rightTurnTime += dt;
	}
	else
		m_rightTurnTime = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		m_speed += m_speed1 * speed;
		if (m_fuel > 0)
			m_particles.Emit();
		if (m_sound.getStatus() != sf::Sound::Playing)
			m_sound.play();
	}
	else
	{
		m_sound.pause();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		m_speed -= m_speed1 * speed;
	}                                             
}

const float SAVETIME = 0.5f;
const float REFILLTIME = 0.2f;

void Ship::Update(const float dt)
{
	float speed = dt / 0.0333f;
	m_speed1 += (0.05f - m_speed1) / 10.0f;
	m_speed *= (1 - 0.03f * speed);
	m_velocity.x += cos(m_rotation * 3.1415 / 180.0f) * m_speed * speed;
	m_velocity.y += sin(m_rotation * 3.1415 / 180.0f) * m_speed * speed;
	m_velocity *= 1 - 0.05f * speed;
	float momentalDistance = sqrt(m_velocity.x * m_velocity.x * speed * speed + m_velocity.y * m_velocity.y* speed * speed);
	m_distanceTraveled += momentalDistance;
	m_fuel -= momentalDistance / 25000.0f;
	if (m_fuel < 0)
		m_fuel = 0;
	if (m_refillTime > 0)
	{
		m_refillTime -= dt;
		m_fuel += 0.05f * speed;
		if (m_fuel > 1)
			m_fuel = 1;
	}
	m_position += m_velocity * speed;

	if (m_saveTime > 0)
	{
		m_saveTime -= dt;
		if (m_saveTime < 0)
			m_saveTime = 0;
	}
	
	m_animator.Update(dt);
	m_shadow.Update(dt);

	float centerToTail = m_animator.GetCurrentSprite().getTextureRect().width / 2;
	sf::Vector2f offset(-cos(m_rotation * 3.1415 / 180.0f) * centerToTail, -sin(m_rotation* 3.1415 / 180.0f) * centerToTail);
	m_particles.Update(dt, offset);

	m_scale = clamp(m_speed, 0.0f, 0.45f) / 3.0f + 0.3f * sin(m_saveTime / SAVETIME * 3.14) + 0.3f * sin(m_refillTime/REFILLTIME * 3.14);	
}

void Ship::Draw(sf::RenderWindow& renderer)
{
	m_particles.Draw(renderer);

	sf::Sprite& shadow = m_shadow.GetCurrentSprite();
	float offsetScale = clamp(m_speed, 0.0f, 0.45f) / 0.05625f + 2.0f;
	sf::Vector2f shadowOffset(-2 * offsetScale, 2 * offsetScale);
	shadow.setPosition(m_position + shadowOffset);
	shadow.setRotation(m_rotation);
	shadow.setScale(0.85f - m_scale, 0.85f - m_scale);
	renderer.draw(shadow);

	if (m_saveTime > 0)
	{
		m_cross.setColor(sf::Color(255, 255, 255, m_saveTime / SAVETIME * 50));
		m_cross.setPosition(m_position);
		m_cross.setScale(0.5f + 0.5 * (m_saveTime) / SAVETIME, 0.5f + 0.5 * (m_saveTime) / SAVETIME);
		m_cross.setRotation(m_saveTime / SAVETIME * 180 + m_rotation);
		m_cross.setOrigin(m_cross.getLocalBounds().width / 2, m_cross.getLocalBounds().height / 2);
		renderer.draw(m_cross);
	}

	sf::Sprite& sprite = m_animator.GetCurrentSprite();
	sprite.setPosition(m_position);
	sprite.setRotation(m_rotation);
	sprite.setScale(0.85f + m_scale, (0.85f + m_scale) * m_orientation);
	renderer.draw(sprite);
}

void Ship::DrawMini(sf::RenderWindow& renderer)
{
	
	//sf::RectangleShape rect2;
	sf::ConvexShape rect2(3);
	rect2.setPoint(0, sf::Vector2f(250, 0));
	rect2.setPoint(1, sf::Vector2f(-250, -250));
	rect2.setPoint(2, sf::Vector2f(-250, 250));
	rect2.setPosition(m_position);
	rect2.setFillColor(sf::Color(255,255,255,255));
	rect2.setRotation(m_rotation);
	renderer.draw(rect2);
}

void Ship::Save(const Survivor& survivor)
{
	if (m_capacity > 0 && !survivor.IsSaved())
	{
		survivor.Save(GetPosition());
		m_capacity--;
		m_sound2.play();
		m_saveTime = SAVETIME;
	}
}

void Ship::Save()
{
}

const sf::Vector2f& Ship::GetPosition()
{
	return m_position;
}

const float Ship::GetFuel()
{
	return m_fuel;
}

void Ship::UnloadPassangers()
{
	m_capacity = 10;
}

const int Ship::GetNumberOfPassengers()
{
	return 10 - m_capacity;
}

const int Ship::GetMaxCapacity()
{
	return 10;
}

void Ship::Lower()
{
}

void Ship::RefillFuel()
{
	m_refillTime = REFILLTIME;
	m_particles.FireUp();
	Camera::GetInstance().Shake(1.0f, 50);
	m_speed1 = 0.1;
}

const float Ship::GetSpeed1()
{
	return m_speed1;
}