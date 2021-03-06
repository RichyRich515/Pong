#pragma once

#include "globals.hpp"
#include <vector>
#include "particle.hpp"
#include "Color.hpp"

class ParticleEmitter
{
public:
	size_t poolsize; // max particles
	std::vector<Particle *> v;

	sf::RectangleShape shape;

	float duration; // how long the particle system exists
	bool active; // if not active, don't draw or update
	bool looping; // restart after duration?
	bool warm; // start particles in play already?

	bool burst;
	// if burst, particles per burst
	// otherwise particles per second
	size_t emission;
	float spawnTime;
	float spawnClock;

	sf::Vector2f position; // position in world space that particle emitter exists

	// How long each particle lives, random val between low and high
	float lifeLow;
	float lifeHigh;

	// selects random velocity between low and high
	float startVelocityLow;
	float startVelocityHigh;

	sf::Vector2f acceleration;
	float maxVelocity;

	// Selects random value between range at birth of particle
	float directionLow;
	float directionHigh;

	// TODO: make this a vector of colors, so "rainbow" blending is possible
	// Born with start color then linear RGBA blend to end color over time
	sf::Color startColor;
	sf::Color endColor;

	// initializes the internal vector to hardcoded value of 500
	ParticleEmitter()
	{
		poolsize = 500;
		ParticleEmitter(poolsize);
	}

	// initializes the internal vector
	ParticleEmitter(size_t maxsize)
	{
		poolsize = maxsize;
		v = std::vector<Particle *>(poolsize);
		for (size_t i = 0; i < poolsize; ++i)
		{
			v[i] = new Particle();
		}
	}

	// render window to draw the particles to
	void draw(sf::RenderWindow & window)
	{
		if (active)
		{
			for (size_t i = 0; i < poolsize; ++i)
			{
				if (v[i]->alive)
					window.draw(*v[i]);
			}
		}
	}

	// delta time
	void update(float dt)
	{
		if (active)
		{
			bool spawn = false;
			size_t spawns = 0; // for burst

			spawnClock += dt;
			// TODO: looping and not burst
			if (looping && spawnClock >= spawnTime)
			{
				spawnClock = 0;
				spawn = true;
			}
			for (size_t i = 0; i < poolsize; ++i)
			{
				if (v[i]->alive)
				{
					v[i]->update(dt, acceleration);
				}
				else if (spawn)
				{
					v[i]->alive = true;
					v[i]->setShape(shape);
					v[i]->setPosition(position);
					float dir = random(directionLow, directionHigh);
					float vel = random(startVelocityLow, startVelocityHigh);
					v[i]->velocity = sf::Vector2f(vel * cos(toRAD(dir)), vel * sin(toRAD(dir)));
					v[i]->lifetime = random(lifeLow, lifeHigh);
					v[i]->life = 0;
					v[i]->startcolor = startColor;
					v[i]->endcolor = endColor;
					if (burst)
					{
						if (++spawns > emission)
						{
							spawn = false;
						}
					}
					else
					{
						spawn = false;
					}
				}
			}
		}
	}

	void boom()
	{
		size_t spawns = 0;
		for (size_t i = 0; i < poolsize; ++i)
		{
			if (!v[i]->alive)
			{
				v[i]->alive = true;
				v[i]->setShape(shape);
				v[i]->setPosition(position);
				float dir = random(directionLow, directionHigh);
				float vel = random(startVelocityLow, startVelocityHigh);
				v[i]->velocity = sf::Vector2f(vel * cos(toRAD(dir)), vel * sin(toRAD(dir)));
				v[i]->lifetime = random(lifeLow, lifeHigh);
				v[i]->life = 0;
				v[i]->startcolor = startColor;
				v[i]->endcolor = endColor;
				if (++spawns >= emission)
					break;
			}
		}
	}

	// TODO: this
	void init()
	{
		if (burst)
		{
			if (looping)
			{
				spawnTime = duration;
				spawnClock = spawnTime;
			}
			else
			{
				//boom();
			}
		}
		else
		{
			spawnTime = 1.0f / emission;
			spawnClock = 0.0f;
		}
	}

	// Copy constructor overload
	// Really shouldn't be using this...
	ParticleEmitter(ParticleEmitter const& src)
	{
		*this = src;
		
		v = std::vector<Particle *>(poolsize);
		for (size_t i = 0; i < poolsize; ++i)
		{
			v[i] = new Particle();
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