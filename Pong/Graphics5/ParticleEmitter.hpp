#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "particle.hpp"

class ParticleEmitter
{
public:
	size_t poolsize;
	std::vector<Particle> v;
	sf::Vector2f acceleration;
	sf::Vector2f direction;

	std::vector<Particle> const& update()
	{
		for (size_t i = 0; i < poolsize; ++i)
		{
			if (v[i].alive)
			{

			}
		}
	}
};