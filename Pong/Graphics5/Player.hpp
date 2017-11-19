#pragma once

#include "SFML\Graphics.hpp"

typedef enum
{
	normal = 0,
} Player_State;

class Player : public sf::RectangleShape
{
public:
	int lives;
	int health;
	Player_State state;

	// Default constructor
	Player()
	{
		lives = 3;
		health = 1;
		state = normal;
		this->setSize(sf::Vector2f(25, 25));
		this->setFillColor(sf::Color::Yellow);
	}
};