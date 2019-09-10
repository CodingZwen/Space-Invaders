#pragma once
#include "Entity.h"
class Enemy : public Entity
{

	//0 is left 1 right
	bool Bdirection;
	float steptime;
	float stepTimeBuffer;
	enum Direction { LEFT,RIGHT };

	float stepFactor = 6.f;
	float timeToReduceSteps;
public:
	Enemy(const sf::Texture &enemysheet,
		sf::Vector2f spawnpos,
		sf::FloatRect enemyarea, 
		float steptime = 0.8,
		float timetoreducesteps=20.);
	virtual ~Enemy();


	void StepDown();
	void setStepTime(float _stepTime);
	void reduceStepTime();
	void update(sf::Time elapsed);
	void draw(sf::RenderTarget &target);
	void handleEnemyArea();

	void changeDirection() {
		stepTimeBuffer = 99.f;
		Bdirection = !Bdirection; }

	void setTimeforReduceSteps(float reduceTime);

};

