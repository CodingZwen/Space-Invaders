#pragma once
#include "Entity.h"
class Enemy : public Entity
{

	//0 is left 1 right
	bool Bdirection;
	float stepFactor = 6.f;
	float timeToReduceSteps;
	float steptime;
	float stepTimeBuffer;

	
public:
	Enemy(const sf::Texture &enemysheet,
		sf::Vector2f spawnpos,
		sf::FloatRect enemyarea, sf::Color c,
		float steptime = 0.8,
		float timetoreducesteps=20.);
	virtual ~Enemy();


	void setStepTime(float _stepTime);
	void reduceStepTime();
	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);


	void changeDirection();

	void setTimeforReduceSteps(float reduceTime);

};

