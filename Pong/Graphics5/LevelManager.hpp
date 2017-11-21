#pragma once

#include "globals.hpp"
#include <iostream>
#include <fstream>
#include "SFML\Graphics.hpp"

constexpr unsigned TILE_WIDTH = 50;
constexpr unsigned TILE_HEIGHT = 50;
constexpr unsigned X_TILES = 18;
constexpr unsigned Y_TILES = 18;

typedef enum
{
	bad_tile = -1,
	ground = 0,
	wall,
	rock,
	movable_rock,
	door,
	stair_up,
	stair_down,
	chest,

	last_tile = 99
} Tile_Type;

static sf::Color getTileColor(int t)
{
	sf::Color c;
	// TODO: use textures or something?
	switch (t)
	{
	case ground:
		c = sf::Color(130, 133, 120);
		break;
	case wall:
		c = sf::Color(10, 10, 10);
		break;
	case rock:
		c = sf::Color(127, 127, 127);
		break;
	case movable_rock:
		c = sf::Color(144, 144, 144);
		break;
	case door:
		c = sf::Color(255, 255, 50);
		break;
	case stair_up:
		c = sf::Color(111, 33, 111);
		break;
	case stair_down:
		c = sf::Color(33, 111, 33);
		break;
	case chest:
		c = sf::Color(111, 255, 255);
		break;
	default:
		c = sf::Color(255, 0, 255);
	};
	return c;
}

class Tile : public sf::RectangleShape
{
public:
	Tile(int col, int row, /*Tile_Type*/ int t)
	{
		this->setSize(sf::Vector2f(TILE_WIDTH, TILE_HEIGHT));
		this->setPosition(col * TILE_WIDTH, row * TILE_HEIGHT);
		// TODO: proper coloring/texturing of tiles
		this->setFillColor(getTileColor(t));
	}
};

class LevelMap
{
public:
	Tile* tiles[X_TILES][Y_TILES];

	sf::RenderTexture LevelTexture;
	sf::Sprite LevelSprite;
	// TODO: default constructor
	LevelMap() {}

	LevelMap(std::string file)
	{
		std::ifstream infile;
		infile.open(file);
		int row = 0;
		int col = 0;
		int t = 0;

		LevelTexture.create(s_width, s_height);
		LevelTexture.clear();

		while (infile >> t)
		{
			// TODO: error checking load
			tiles[col][row] = new Tile(col, row, /*(Tile_Type)*/t);

			std::cout << std::hex << t;
			LevelTexture.draw(*tiles[col][row]);
			// TODO: hardcoded values
			if (++col == X_TILES)
			{
				std::cout << std::endl;
				++row;
				col = 0;
			}
		}

		LevelTexture.display();
		const sf::Texture& texture = LevelTexture.getTexture();
		LevelSprite.setTexture(texture);
	}
};