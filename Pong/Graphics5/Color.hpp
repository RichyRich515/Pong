#pragma once
#include "globals.hpp"

// lerpRGBA: performs a linear interpolation between two colors in RGBA color space per t
//	sf::Color c1: Start color
//	sf::Color c2: End color
//	float t: point between c1 and c2, limit: 0.0f and 1.0f
sf::Color lerpRGBA(sf::Color c1, sf::Color c2, float t)
{
	assert(t <= 1.0f && t >= 0.0f && " invalid t value");

	// TODO: type missmatch
	float r, g, b, a;
	r = lerp(c1.r, c2.r, t);
	g = lerp(c1.g, c2.g, t);
	b = lerp(c1.b, c2.b, t);
	a = lerp(c1.a, c2.a, t);

	return sf::Color(r, g, b, a);
}

