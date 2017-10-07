#pragma once

#include <SFML\Graphics.hpp>

class Particle : sf::RectangleShape
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
};