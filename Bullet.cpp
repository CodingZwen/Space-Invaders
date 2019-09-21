#include "Bullet.h"



Bullet::Bullet(const sf::Vector2f &spawnPos, Direction dir,  float dieTime, sf::Texture *bulletTexture)
{

	float speed = 500;
	int sizex = 8;
	int sizey = 20;
	livedTime = 0;
	timeToDie = dieTime;

	if (dir == Direction::UP)
	{
		velocity = sf::Vector2f(0, -speed);
	}
	else if (dir == Direction::DOWN)
	{
		velocity = sf::Vector2f(0, speed);
	}
	else {
		velocity = sf::Vector2f(speed, 0.f);
	}


	shape.setPosition(spawnPos);
	shape.setFillColor(sf::Color::Green);
	shape.setSize(sf::Vector2f(static_cast<float>(sizex),static_cast<float>( sizey)));
	shape.setOrigin(sizex / 2.f, sizey / 2.f);


}


Bullet::~Bullet()
{
}

void Bullet::draw(sf::RenderTarget & target)
{
	target.draw(shape);
}

void Bullet::update(sf::Time elapsed)
{

	if (shape.getPosition().y<0||shape.getPosition().y >2048)kill();

	livedTime += elapsed.asSeconds();
	shape.move(velocity*elapsed.asSeconds());

	if (livedTime > timeToDie)life = false;
}
