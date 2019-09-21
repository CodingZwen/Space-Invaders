#pragma once
#include "Animation.h"
#include "MovementComponent.h"
class Entity
{

protected :
	bool life = true;
	bool outofWindow;

	float livedTime;
	float timeToDie;
	sf::FloatRect screenBounds;

	Animation animation;
	std::shared_ptr<MovementComponent> movementComponent;

public:
	Entity();
	virtual ~Entity();
	virtual void update(sf::Time elapsed) = 0;
	virtual void draw(sf::RenderTarget &target) = 0;

	void setScreenBounds(sf::Vector2i screenDimensions);
	void kill() { life = false; }

	//checks
	bool isAlive() { return life; }
	bool checkForScreenBounds();

	void createMovementComponent(const float maxVelocity, const float acceleration, const float decelaration);
	
	//gets
	const sf::Sprite &getSprite() { return this->animation.getSprite(); }
	MovementComponent* const getMovementptr() { return movementComponent.get();}

};

