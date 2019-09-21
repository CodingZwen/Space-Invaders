#include "Enemy.h"





Enemy::Enemy(const sf::Texture & enemySheet, sf::Vector2f spawnPos,
	sf::FloatRect enemyArea, sf::Color c,
	float stepTime,
	float timetoreducesteps)
{
	animation.init(enemySheet, 0, 0, 12, 10, 2, 1);
	createMovementComponent(1000.f*stepFactor, 500* stepFactor, 400*stepFactor);
	movementComponent->setPosition(spawnPos);

	this->setScreenBounds(sf::Vector2i(enemyArea.width,enemyArea.height));
	this->steptime = stepTime;
	stepTimeBuffer = 0.f;
	Bdirection = 0;

	timeToReduceSteps = timetoreducesteps;

	animation.setColor(c);
	
}

Enemy::~Enemy()
{
}



void Enemy::reduceStepTime()
{
	if(steptime>0.1)
	steptime -= 0.1;
}

void Enemy::update(sf::Time elapsed)
{

	stepTimeBuffer += elapsed.asSeconds();
	livedTime += elapsed.asSeconds();

	//simulates the input from the enemy
	if (stepTimeBuffer > steptime)
	{


		Bdirection ? movementComponent->move(sf::Vector2f(-896* stepFactor, 0)) :
					 movementComponent->move(sf::Vector2f(896* stepFactor, 0));


		stepTimeBuffer = 0.f;

		if (static_cast<int>(livedTime) %
			static_cast<int>(timeToReduceSteps) == 0)reduceStepTime();

		
	}


	movementComponent->update(elapsed.asSeconds());
	animation.update(elapsed);


}

void Enemy::draw(sf::RenderTarget & target)
{
	animation.draw(target);
}




void Enemy::changeDirection()
{
	
		stepTimeBuffer = 64.f;
		Bdirection = !Bdirection; 
}

void Enemy::setTimeforReduceSteps(float reduceTime)
{if(reduceTime>1)
	timeToReduceSteps = reduceTime;
}

