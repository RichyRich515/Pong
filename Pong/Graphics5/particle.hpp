#pragma once

#include <SFML\Graphics.hpp>

class Particle : public sf::RectangleShape
{
public:
	bool alive;
	float lifetime;
	sf::Vector2f velocity;

	Particle()
	{
		alive = false;
		lifetime = 0.0f;
		velocity = sf::Vector2f(0, 0);
	}

	Particle const& update(float dt, sf::Vector2f a)
	{
		velocity = sf::Vector2f(a.x * dt, a.y * dt);
		sf::Vector2f disp = sf::Vector2f(velocity.x * dt, velocity.y * dt);
		move(disp);

		return *this;
	}
};