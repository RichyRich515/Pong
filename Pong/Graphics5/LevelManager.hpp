#pragma once

#include "globals.hpp"
#include <iostream>
#include <fstream>
#include <bitset>
#include "SFML\Graphics.hpp"

enum
{
	Empty = 0,
	W,
	S,
	SW,
	E,
	EW,
	ES,
	ESW,
	N,
	NW,
	NS,
	NSW,
	NE,
	NEW,
	NES,
	NESW,
};

class Tile
{
public:
	bool n, e, s, w;

	/*
	 *	makes empty tile
	 */
	Tile()
	{
		n = false;
		e = false;
		s = false;
		w = false;
	}

	/* 
	 *	takes an int (0 - 15) that uses the bits to represent which walls
	 *	0th idx = right wall
	 *	1 = top wall
	 *	2 = left wall
	 *	3 = bottom wall
	 */
	Tile(int walls)
	{
		n = walls & N;
		e = walls & E;
		s = walls & S;
		w = walls & W;
	}
};

class LevelMap
{
public:
	Tile tiles[36][36];

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
		while (infile >> t)
		{
			tiles[col][row] = Tile(t);

			std::cout << std::hex << t;
			// TODO: hardcoded values
			if (++col == 36)
			{
				std::cout << std::endl;
				++row;
				col = 0;
			}
		}

		LevelTexture.create(s_width, s_height);
		LevelTexture.clear();
		
		for (unsigned y = 0; y < 36; ++y)
		{
			for (unsigned x = 0; x < 36; ++x)
			{
			
				//std::cout << tiles[col][row].n;
				if (tiles[x][y].n)
				{
					sf::RectangleShape l(sf::Vector2f(25, 2));
					l.setPosition(x * 25, y * 25);
					l.setFillColor(sf::Color::Red);
					LevelTexture.draw(l);
				}
				if (tiles[x][y].e)
				{
					sf::RectangleShape l(sf::Vector2f(2, 25));
					l.setPosition(x * 25 + 25, y * 25);
					l.setFillColor(sf::Color::Green);
					LevelTexture.draw(l);
				}
				if (tiles[x][y].s)
				{
					sf::RectangleShape l(sf::Vector2f(25, 2));
					l.setPosition(x * 25, y * 25 + 25);
					l.setFillColor(sf::Color::Blue);
					LevelTexture.draw(l);
				}
				if (tiles[x][y].w)
				{
					sf::RectangleShape l(sf::Vector2f(2, 25));
					l.setPosition(x * 25, y * 25);
					l.setFillColor(sf::Color::Yellow);
					LevelTexture.draw(l);
				}
			}
		}
		LevelTexture.display();
		const sf::Texture& texture = LevelTexture.getTexture();
		LevelSprite.setTexture(texture);
	}
};