#pragma once

#include "Entity.h"

class Player : public Entity
{
	unsigned int currentPoints = 0;
	unsigned short lives=3;

public:
	Player(sf::Texture &playertexture,sf::Vector2f spawnPos);
	virtual ~Player();

	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);
	
	void Die();
	void drawOneLife() {if(lives>0)lives--; };
	void inkrementPoints(float factor = 1.f) { currentPoints += (10 * factor); }
	unsigned int &getPoints() { return currentPoints; }

	const unsigned short &getLives() { return lives; }

};

