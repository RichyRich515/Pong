#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "particle.hpp"
#include "Color.hpp"

class ParticleEmitter
{
public:
	size_t poolsize; // max particles
	std::vector<Particle *> v;

	float duration; // how long the particle system exists
	bool looping; // restart after duration?
	
	bool burst;

	// if burst, particles per burst
	// otherwise particles per second
	size_t emission;

	sf::Vector2f position; // position in world space that particle emitter exists

	// selects random velocity between low and high
	float startVelocityLow;
	float startVelocityHigh;

	sf::Vector2f acceleration;
	float maxVelocity;

	// Selects random value between range at birth of particle
	float directionLow;
	float directionHigh;
	
	// How long each particle lives, random val between low and high
	float lifeLow;
	float lifeHigh;

	// TODO: make this a vector of colors, so rainbow blending is possible
	// Born with start color then linear RGBA blend to end over time
	sf::Color startColor;
	sf::Color endColor;

	// doesnt do much, simply initializes the internal vector
	ParticleEmitter(size_t maxsize)
	{
		poolsize = maxsize;
		v = std::vector<Particle *>(poolsize);
		for (size_t i = 0; i < poolsize; ++i)
		{
			Particle* temp = new Particle();
			v[i] = temp;
		}
	}

	// render window to draw the particles to
	void draw(sf::RenderWindow & window)
	{
		for (size_t i = 0; i < poolsize; ++i)
		{
			if (v[i]->alive)
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