#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

# define M_PI 3.14159265358979323846


#include <fstream>
#include <stack>
#include <iostream>
#include "Animation.h"



enum movement_states {
	MOVING_UP=1, MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT,
	STANDING
};

class MovementComponent
{

private: 

	 Animation  *ptrAnimation = nullptr;
	 short lastState;

	//wenn man daraus einen 2f machen würde könnte man eine richtung
	//langsamer machen um z.b einen sturm von oben zu simulieren :D
	float maxVelocity;
	float decelaration,acceleration;
	float timeNotMoved;
	float velocityFreezetime;
	
	bool freezeVelo =false;
	bool isColliding = false;
	

	sf::Vector2f velocity;
	sf::Vector2f currentPosition;
	sf::Vector2f oldPosition;
	float R = 16;

	//initalize functions

	static float RADIANT;
public:
	sf::Vector2f lockedVelocity;
	MovementComponent(Animation &Animation,const float maxVelocity, float beschleunigung, float verzoegerung);
	virtual ~MovementComponent();

	bool isAFK();
	void freezeMovement() { freezeVelo = true; }
	const bool getStates(const short unsigned state);
	sf::FloatRect getGlobalBounds() const;

	//sets old pos to current pos, for mapchange f.e
	void resetOldPos();

	//accessors
	const sf::Vector2f  &getVelocity(float multiplier=1.f)const ;
	const sf::Vector2f &getPosition() const;
	const sf::Vector2f &getOldPosition() const;
	const float getMaxVelocity();
	const float getAngleToTarget(sf::Vector2f target);
	const float getRadius() { return R; }
	 
	
	const sf::Vector2i &getPosAsFieldNumber(unsigned int tilesize);

	float getDistanceToTarget(sf::Vector2f target);
	void moveToTarget(const sf::Vector2f &targetPos);

	void move(const float dir_x, const float dir_y,const float &dt);
	void move(const sf::Vector2f velo);
	void moveWithoutAcceleration(const sf::Vector2f velo);
	void pushToRight(float factor=0.75f);
	void pushToLeft(float factor = 0.75f);

	void moveRandom();

	void setOldPosition();
	void setPosition(const sf::Vector2f &pos, bool resetOldpos =false);
	void setCollide() { isColliding = true; }
	void changeAttributs(float maxVelo, float acceleration, float decceleration);

	void update(const float &dt);

	bool isStanding();
};




#endif