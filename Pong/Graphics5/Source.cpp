#include "globals.hpp"
#include "keyboard.hpp"

#include <iostream>
#include <string>
#include <vector>


constexpr float MIN_BALL_SPEED = 200.0f;
constexpr float MAX_PADDLE_SPEED = 200.0f;
float bspeed = MIN_BALL_SPEED;
float pspeed = MIN_BALL_SPEED;
float xmod = 1, ymod = 1;
int p1mod = 0, p2mod = 0;

unsigned s_width = 600;
unsigned s_height = 800;

int p1score = 0;
int p2score = 0;

int main()
{
	srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "Ping");
	sf::Clock timer;
	unsigned dt = 0;
	
	// Init
	centerOrigin(ball);
	centerOrigin(p1);
	centerOrigin(p2);
	ball.setPosition(ball.getSize().x / 2.0f, s_height / 2.0f);
	p1.setPosition(s_width / 2.0f, 50);
	p2.setPosition(s_width / 2.0f, s_height - getWidth(p2) / 2.0f - 50);

	sf::SoundBuffer boopBuffer;
	if (!boopBuffer.loadFromFile("sfx\\boop.wav"))
		return -1;
	sf::Sound boopSound;
	boopSound.setBuffer(boopBuffer);

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

		ball.move(sf::Vector2f(xmod * bspeed * dt, ymod * bspeed * dt));

		float bh = getWidth(ball) / 2.0f;
		float bx = ball.getPosition().x;
		float by = ball.getPosition().y;
		float bw = ball.getPosition().x - bh;
		float bn = ball.getPosition().y - bh;
		float be = ball.getPosition().x + bh;
		float bs = ball.getPosition().y + bh;

		if (bw <= 0)
		{
			ball.setPosition(0 + bh, by);
			xmod = 1;
		}
		else if (be >= s_width)
		{
			ball.setPosition(s_width - bh, by);
			xmod = -1;
		}

		if (by < s_height / 2.0f)
		{
			if (bn <= 0)
			{
				ball.setPosition(rand() % (unsigned)(s_width + bh * 2) - bh, s_height / 2.0f);
				bspeed = MIN_BALL_SPEED;
				ymod = 1;
			}
			else if (ball.getGlobalBounds().intersects(p1.getGlobalBounds()))
			{
				ymod = 1;
				bspeed += 10.0f;
				ball.setPosition(bx, p1.getPosition().y + getHeight(p1) / 2.0f + bh);
				ball.setFillColor(randcol());
				boopSound.play();
			}
		}
		else
		{
			if (bs >= s_height)
			{
				ball.setPosition(rand() % (unsigned)(s_width + bh * 2) - bh, s_height / 2.0f);
				bspeed = MIN_BALL_SPEED;
				ymod = -1;
			}
			else if (ball.getGlobalBounds().intersects(p2.getGlobalBounds()))
			{
				ymod = -1;
				bspeed += 10.0f;
				ball.setPosition(bx, p2.getPosition().y - getHeight(p2) / 2.0f - bh);
				ball.setFillColor(randcol());
				boopSound.play();
			}
		}
		
		checkKeyboard();

		p1.move(pspeed * p1mod * dt, 0);
		p2.move(pspeed * p2mod * dt, 0);

		if ((p1.getPosition().x + getWidth(p1) / 2.0f) > s_width)
		{
			p1.setPosition(s_width - getWidth(p1) / 2.0f, p1.getPosition().y);
		}
		else if ((p1.getPosition().x - getWidth(p1) / 2.0f) < 0)
		{
			p1.setPosition(getWidth(p1) / 2.0f, p1.getPosition().y);
		}

		if ((p2.getPosition().x + getWidth(p2) / 2.0f) > s_width)
		{
			p2.setPosition(s_width - getWidth(p2) / 2.0f, p2.getPosition().y);
		}
		else if ((p2.getPosition().x - getWidth(p2) / 2.0f) < 0)
		{
			p2.setPosition(getWidth(p2) / 2.0f, p2.getPosition().y);
		}

		window.clear();
		window.draw(ball);
		window.draw(p1);
		window.draw(p2);
		window.display();
	}

	return 0;
}