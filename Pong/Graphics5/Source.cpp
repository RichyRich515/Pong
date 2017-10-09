#include "globals.hpp"
#include "keyboard.hpp"
#include "ParticleEmitter.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

constexpr float MIN_BALL_SPEED = 200.0f;
constexpr float MAX_PADDLE_SPEED = 200.0f;
float bspeed = MIN_BALL_SPEED;
float pspeed = MIN_BALL_SPEED;
float xmod = 1, ymod = 1;
int p1mod = 0, p2mod = 0;

bool ballMoving = false;

unsigned s_width = 600;
unsigned s_height = 800;

int p1score = 0;
int p2score = 0;

float ballSpeedIncrease = 25.f;
float ballPauseTimer = 0.0f;
constexpr float BALL_PAUSE_TIME = 2.0f; // seconds\

sf::Color p1Color = sf::Color(255, 64, 64);
sf::Color p2Color = sf::Color(0, 255, 127);

sf::RectangleShape directionLine;

static ParticleEmitter emitter1 = ParticleEmitter(500);

// set the direction line to point the right way
void setDirectionLine()
{
	float dir = 0;
	if (xmod > 0 && ymod > 0)
	{
		dir = 225;
		directionLine.setRotation(45);
		emitter1.directionLow = dir - 15;
		emitter1.directionHigh = dir + 15;
	}
	else if (xmod < 0 && ymod > 0)
	{
		dir = 315;
		directionLine.setRotation(135);
		emitter1.directionLow = dir - 15;
		emitter1.directionHigh = dir + 15;
	}
	else if (xmod < 0 && ymod < 0)
	{
		dir = 45;
		directionLine.setRotation(225);
		emitter1.directionLow = dir - 15;
		emitter1.directionHigh = dir + 15;
	}
	else if (xmod > 0 && ymod < 0)
	{
		dir = 135;
		directionLine.setRotation(315);
		emitter1.directionLow = dir - 15;
		emitter1.directionHigh = dir + 15;
	}
	directionLine.setPosition(ball.getPosition());
}

// reset the ball to the middle line
void resetBall()
{
	emitter1.active = false;
	ball.setPosition(rand() % (unsigned)(s_width + ball.getSize().x) - ball.getSize().x / 2.0f, s_height / 2.0f);
	bspeed = MIN_BALL_SPEED;
	ballMoving = false;
	setDirectionLine();
	return;
}

int main()
{
	srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "Ping");
	sf::Clock timer;
	
	// Init
	centerOrigin(ball);
	centerOrigin(p1);
	centerOrigin(p2);
	ball.setPosition(ball.getSize().x / 2.0f, s_height / 2.0f);
	ball.setFillColor(sf::Color(255, 255, 100));
	p1.setPosition(s_width / 2.0f, 50);
	p2.setPosition(s_width / 2.0f, s_height - 50);
	p1.setFillColor(p1Color);
	p2.setFillColor(p2Color);

	sf::SoundBuffer boopBuffer;
	if (!boopBuffer.loadFromFile("sfx\\boop.wav"))
		return -1;
	sf::Sound boopSound;
	boopSound.setBuffer(boopBuffer);

	if (!courierFont.loadFromFile("font\\cour.ttf"))
		return -1;
	sf::Text p1scoreText;
	sf::Text p2scoreText;
	p1scoreText.setFont(courierFont);
	p2scoreText.setFont(courierFont);
	p1scoreText.setCharacterSize(60);
	p2scoreText.setCharacterSize(60);
	p1scoreText.setString("00");
	p2scoreText.setString("00");
	p1scoreText.setPosition(0, s_height / 2.0f - p2scoreText.getCharacterSize() - 15);
	p2scoreText.setPosition(s_width - p2scoreText.findCharacterPos(2).x, s_height / 2.0f - 10);

	directionLine = sf::RectangleShape(sf::Vector2f(75.0f, 2.0f));
	directionLine.setFillColor(sf::Color::Red);
	directionLine.setOrigin(0, 1.0f);

	sf::RectangleShape midline(sf::Vector2f(s_width, 2.0f));
	centerOrigin(midline);
	midline.setPosition(s_width / 2.0f, s_height / 2.0f);

	emitter1.shape = sf::RectangleShape(sf::Vector2f(2.5f, 2.5f));
	emitter1.startColor = sf::Color(0, 0, 255, 255);
	emitter1.endColor = sf::Color(0, 0, 0, 0);
	emitter1.startVelocityLow = 75.0f;
	emitter1.startVelocityHigh = 200.0f;
	emitter1.duration = 1.0f;
	emitter1.emission = 100;
	emitter1.burst = false;
	emitter1.directionLow = 0;
	emitter1.directionHigh = 360;
	emitter1.acceleration = sf::Vector2f(0, 0);
	emitter1.lifeLow = 0.0f;
	emitter1.lifeHigh = 1.5f;
	emitter1.looping = true;
	emitter1.warm = false;
	emitter1.init();

	resetBall();
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

		if (ballMoving)
		{
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
				setDirectionLine();
			}
			else if (be >= s_width)
			{
				ball.setPosition(s_width - bh, by);
				xmod = -1;
				setDirectionLine();
			}

			if (by < s_height / 2.0f)
			{
				if (bn <= 0)
				{
					++p2score;
					ymod = 1;
					resetBall();
					boopSound.play();
				}
				else if (ball.getGlobalBounds().intersects(p1.getGlobalBounds()))
				{
					ymod = 1;
					bspeed += ballSpeedIncrease;
					ball.setPosition(bx, p1.getPosition().y + getHeight(p2) / 2.0f + bh);
					setDirectionLine();
					boopSound.play();
				}
			}
			else
			{
				if (bs >= s_height)
				{
					++p1score;
					ymod = -1;
					resetBall();
					boopSound.play();
				}
				else if (ball.getGlobalBounds().intersects(p2.getGlobalBounds()))
				{
					ymod = -1;
					bspeed += ballSpeedIncrease;
					ball.setPosition(bx, p2.getPosition().y - getHeight(p2) / 2.0f - bh);
					setDirectionLine();
					boopSound.play();
				}
			}
		}
		else if (ballPauseTimer >= BALL_PAUSE_TIME)
		{
			ballPauseTimer = 0;
			ballMoving = true;
			emitter1.active = true;
		}
		else
		{
			ballPauseTimer += dt;
		}

		checkKeyboard();

		p1.move(pspeed * p1mod * dt, 0);
		p2.move(pspeed * p2mod * dt, 0);

		if ((p1.getPosition().x + getWidth(p1) / 2.0f) > s_width)
			p1.setPosition(s_width - getWidth(p1) / 2.0f, p1.getPosition().y);
		else if ((p1.getPosition().x - getWidth(p1) / 2.0f) < 0)
			p1.setPosition(getWidth(p1) / 2.0f, p1.getPosition().y);
		if ((p2.getPosition().x + getWidth(p2) / 2.0f) > s_width)
			p2.setPosition(s_width - getWidth(p2) / 2.0f, p2.getPosition().y);
		else if ((p2.getPosition().x - getWidth(p2) / 2.0f) < 0)
			p2.setPosition(getWidth(p2) / 2.0f, p2.getPosition().y);

		// score texts
		// TODO: this but better
		stringstream p1scorebuff;
		p1scorebuff << setfill('0') << setw(2) << p1score;;
		stringstream p2scorebuff;
		p2scorebuff << setfill('0') << setw(2) << p2score;;
		p1scoreText.setString(p1scorebuff.str());
		p2scoreText.setString(p2scorebuff.str());

		emitter1.position = ball.getPosition();
		emitter1.update(dt);


		window.clear();
		window.draw(p1scoreText);
		window.draw(p2scoreText);
		window.draw(midline);
		if (ballPauseTimer)
			window.draw(directionLine);
		emitter1.draw(window);
		window.draw(ball);
		window.draw(p1);
		window.draw(p2);
		window.display();
	}

	return 0;
}