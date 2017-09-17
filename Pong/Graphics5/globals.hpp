#pragma once
#include <SFML\Graphics.hpp>

extern float bspeed;
extern float pspeed;
extern float xmod, ymod;
extern int p1mod, p2mod;

extern unsigned s_width;
extern unsigned s_height;

sf::RectangleShape ball(sf::Vector2f(25.f, 25.f));
sf::RectangleShape p1(sf::Vector2f(63.5f, 13.5f));
sf::RectangleShape p2(sf::Vector2f(63.5f, 13.5f));

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

sf::Color randcol()
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255);
}