#pragma once

#include <SFML\Graphics.hpp>
#include "Color.hpp"

class Particle : public sf::RectangleShape
{
public:
	bool alive;
	float lifetime;
	float life;
	sf::Vector2f velocity;
	float rotationvelocity;

	sf::Color startcolor;
	sf::Color endcolor;

	Particle()
	{
		alive = false;
		lifetime = 0.0f;
		velocity = sf::Vector2f(0, 0);
	}

	void setShape(sf::RectangleShape const& s)
	{
		setOrigin(s.getOrigin());
		setScale(s.getScale());
		setSize(s.getSize());
		setPosition(s.getPosition());
		setRotation(s.getRotation());
		setFillColor(s.getFillColor());
		setOutlineColor(s.getOutlineColor());
		setOutlineThickness(s.getOutlineThickness());
		setTexture(s.getTexture());
		setTextureRect(s.getTextureRect());
	}

	void update(float dt, sf::Vector2f a)
	{
		life += dt;
		if (life >= lifetime)
		{
			alive = false;
		}
		else
		{
			velocity = sf::Vector2f(velocity.x + a.x * dt, velocity.y + a.y * dt);
			sf::Vector2f disp = sf::Vector2f(velocity.x * dt, velocity.y * dt);
			float rot = rotationvelocity * dt;
			move(disp);

			setFillColor(lerpRGBA(startcolor, endcolor, life / lifetime));
		}
	}
};