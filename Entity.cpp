#include "Entity.h"



Entity::Entity()
{

}


Entity::~Entity()
{
}



void Entity::setScreenBounds(sf::Vector2i screenDimensions)
{
	screenBounds.left = 0;
	screenBounds.top = 0;
	screenBounds.width = screenDimensions.x;
	screenBounds.height = screenDimensions.y;

}



bool Entity::checkForScreenBounds()
{
	if (movementComponent->getPosition().x < screenBounds.left
		|| movementComponent->getPosition().x> screenBounds.width
		|| movementComponent->getPosition().y < screenBounds.top
		|| movementComponent->getPosition().y > screenBounds.height)
	{
		return true;
	}
		return  false;
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float decelaration)
{
	this->movementComponent = std::make_shared<MovementComponent>(animation, maxVelocity, acceleration, decelaration);

}
