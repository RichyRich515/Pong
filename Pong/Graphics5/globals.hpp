#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cassert>


constexpr double Gravity = 10.0;
constexpr double PI = 3.141592654;

#define toRAD(d) (d * PI / 180)

extern float s_width;
extern float s_height;

extern int p1score;
extern int p2score;

sf::Font courierFont;

inline float getWidth(sf::Shape const &o)
{
	return o.getLocalBounds().width;
}

inline float getHeight(sf::Shape const &o)
{
	return o.getLocalBounds().height;
}

inline void centerOrigin(sf::Shape &o)
{
	o.setOrigin(o.getLocalBounds().width / 2.0f, o.getLocalBounds().height / 2.0f);
}

// lerp: performs a linear interpolation between two floats per t
//	float p0: initial point
//	float p1: end point
//	float t: point between p1 and p2, limit: 0.0f and 1.0f
inline float lerp(float p0, float p1, float t) {
	assert(t <= 1.0f && t >= 0.0f && " invalid t value");
	return (1 - t) * p0 + t * p1;
}

int random(int l, int h)
{
	return rand() % (h - l + 1) + l;
}