#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "particle.hpp"

class ParticleEmitter
{
public:
	size_t poolsize;
	std::vector<Particle *> v;
	sf::Vector2f acceleration;
	sf::Vector2f direction;

	// delta time, render window to draw to
	void update(float dt, sf::RenderWindow & window)
	{
		for (size_t i = 0; i < poolsize; ++i)
		{
			Particle *p = v[i];
			if (p->alive)
			{
				window.draw(p->update(dt, acceleration));
			}
		}
	}
};