#include "globals.hpp"
#include "keyboard.hpp"
#include "ParticleEmitter.hpp"
#include "Player.hpp"
#include "LevelManager.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

// Character, Controls, Camera
int main()
{
	srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "goodbye");
	sf::Clock timer;

	if (!courierFont.loadFromFile("font\\cour.ttf"))
	{
		return -1;
	}
	
	Player player = Player();
	centerOrigin(player);
	player.setPosition(s_width / 2.0f, s_height / 2.0f);
	
	LevelMap level("Map.txt") ;

	timer.restart();
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		float dt = timer.restart().asSeconds();
		
		checkKeyboard();

		window.clear();
		window.draw(level.LevelSprite);
		window.draw(player);
		window.display();
	}


	return 0;
}