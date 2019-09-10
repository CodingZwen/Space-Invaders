#pragma once
#include "Entity.h"
class Bullet :
	public Entity
{

	short direction;
	sf::Vector2f velocity;
public:
	enum Direction {UP,DOWN};
	bool bisPlayerBullet = false;
	Bullet(const sf::Vector2f &spawnPos,Direction dir,float dieTime, sf::Texture *bulletTexture = nullptr);
	virtual ~Bullet();

	void draw(sf::RenderTarget &target);
	void update(sf::Time elapsed);
	void setNirvana() { shape.setPosition(sf::Vector2f(9999, 9999)); }
	void setPlayerBullet() { bisPlayerBullet = 1; }

	sf::RectangleShape shape;

};

