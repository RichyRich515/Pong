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

sf::Color p1Color = sf::Color(255, 0, 0);
sf::Color p2Color = sf::Color(0, 0, 255);

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
	ball.setPosition(rand() % (unsigned)(s_width + ball.getRadius() * 2) - ball.getRadius(), s_height / 2.0f);
	bspeed = MIN_BALL_SPEED;
	ballMoving = false;
	setDirectionLine();
	return;
}

int main()
{
	srand((unsigned)time(NULL));

	sf::RenderWindow window(sf::VideoMode(s_width, s_height), "2Pong");
	sf::Clock timer;
	
	// Init
	centerOrigin(ball);
	centerOrigin(p1);
	centerOrigin(p2);
	ball.setPosition(ball.getRadius(), s_height / 2.0f);
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
	emitter1.active = false;
	emitter1.init();

	ParticleEmitter burstEmitter1(2000);
	burstEmitter1.shape = sf::RectangleShape(sf::Vector2f(2.0f, 2.0f));
	burstEmitter1.startColor = p1Color;
	burstEmitter1.endColor = sf::Color(0, 0, 0, 0);
	burstEmitter1.startVelocityLow = 0.0f;
	burstEmitter1.startVelocityHigh = 100.0f;
	burstEmitter1.duration = 4.0f;
	burstEmitter1.emission = 2000;
	burstEmitter1.directionLow = -15;
	burstEmitter1.directionHigh = 195;
	burstEmitter1.acceleration = sf::Vector2f(0, 0);
	burstEmitter1.lifeLow = 0.0f;
	burstEmitter1.lifeHigh = 2.0f;
	burstEmitter1.looping = false;
	burstEmitter1.burst = true;
	burstEmitter1.warm = false;
	burstEmitter1.active = true;
	burstEmitter1.init();

	ParticleEmitter burstEmitter2 = burstEmitter1;
	burstEmitter2.startColor = p2Color;
	burstEmitter2.directionLow = 165;
	burstEmitter2.directionHigh = 375;

	ParticleEmitter burstEmitter3 = burstEmitter1;
	burstEmitter3.directionLow = 0;
	burstEmitter3.directionHigh = 360;

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
				burstEmitter3.position = ball.getPosition();
				burstEmitter3.startColor = ball.getFillColor();
				burstEmitter3.boom();
				boopSound.play();
			}
			else if (be >= s_width)
			{
				ball.setPosition(s_width - bh, by);
				xmod = -1;
				setDirectionLine();
				burstEmitter3.position = ball.getPosition();
				burstEmitter3.startColor = ball.getFillColor();
				burstEmitter3.boom();
				boopSound.play();
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
					burstEmitter1.position = p1.getPosition();
					burstEmitter1.boom();
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
					burstEmitter2.position = p2.getPosition();
					burstEmitter2.boom();
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

		ball.setFillColor(lerpRGBA(p1Color, p2Color, ball.getPosition().y / s_height));

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

		burstEmitter1.update(dt);
		burstEmitter2.update(dt);

		window.clear();
		window.draw(p1scoreText);
		window.draw(p2scoreText);
		window.draw(midline);
		emitter1.draw(window);
		burstEmitter1.draw(window);
		burstEmitter2.draw(window);
		window.draw(ball);
		if (ballPauseTimer)
			window.draw(directionLine);
		window.draw(p1);
		window.draw(p2);
		window.display();
	}
	
	if (boopSound.Playing)
		boopSound.stop();


	return 0;
}