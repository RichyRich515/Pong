#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "particle.hpp"

class ParticleEmitter
{
public:
	size_t poolsize; // max particles
	std::vector<Particle *> v;

	float duration; // how long the particle system exists
	bool looping; // restart after duration?
	
	size_t emission; // particles per second

	// selects random velocity between low and high
	float startVelocityLow;
	float startVelocityHigh;

	float maxVelocity;
	sf::Vector2f acceleration;

	// Selects value at birth of particle between two degrees
	float directionLow;
	float directionHigh;
	
	// How long each particle lives, random val between low and high
	float lifeLow;
	float lifeHigh;

	sf::Color startColor;
	sf::Color endColor;

	ParticleEmitter(sf::RectangleShape const& shape, sf::Vector2f accel, size_t maxsize)
	{
		poolsize = maxsize;
		v = std::vector<Particle *>(poolsize);
		for (size_t i = 0; i < poolsize; ++i)
		{
			Particle* temp = new Particle();
			sf::Vector2f tv = sf::Vector2f();
			temp->velocity = tv;
			temp->setShape(shape);
			v[i] = temp;
		}
	}

	// render window to draw to
	void draw(sf::RenderWindow & window)
	{
		for (size_t i = 0; i < poolsize; ++i)
		{
			window.draw(*v[i]);
		}
	}

	// delta time
	void update(float dt)
	{
		for (size_t i = 0; i < poolsize; ++i)
		{
			if (v[i]->alive)
			{
				v[i]->update(dt, acceleration);
			}
		}
	}

	~ParticleEmitter()
	{
		for (size_t i = 0; i < poolsize; ++i)
		{
			delete v[i];
		}
	}
};