#pragma once

#include "globals.hpp"

void checkKeyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// both down, do nothing
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			p1mod = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			p1mod = 1;
		else
			p1mod = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		// both down, do nothing
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			p2mod = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			p2mod = 1;
		else
			p2mod = 0;
	}
}