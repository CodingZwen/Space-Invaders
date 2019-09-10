#include "Player.h"



Player::Player(sf::Texture &playertexture, sf::Vector2f spawnPos)
{
	float factor = 5.f;
	animation.init(playertexture, 0, 0, 13, 8, 1, 1);
	createMovementComponent(4000.f*factor, 2000.f*factor, 1600.f*factor);
	movementComponent->setPosition(spawnPos);
	
}


Player::~Player()
{
}

void Player::update(sf::Time elapsed)
{
	if (lives < 1) {
		movementComponent->freezeMovement();
		Die(); }

	if (checkForScreenBounds())movementComponent->setCollide();

	movementComponent->update(elapsed.asSeconds());
	animation.update(elapsed);
}

void Player::draw(sf::RenderTarget & target)
{
	animation.draw(target);
}

void Player::Die()
{
	animation.setFrames(2);
	animation.setRows(2);
	animation.setRow(1);
	life = false;
}
