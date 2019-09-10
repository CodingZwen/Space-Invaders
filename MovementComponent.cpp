#include "MovementComponent.h"





MovementComponent::MovementComponent(Animation &animation, const float max_Velocity, float beschleunigung, float verzoegerung)
	: ptrAnimation(&animation), maxVelocity(max_Velocity), acceleration(beschleunigung), decelaration(verzoegerung)
{
	currentPosition = animation.getPosition();
	velocity = sf::Vector2f(0.f,0.f);



	if (ptrAnimation)ptrAnimation->setPosition(currentPosition);
}

MovementComponent::~MovementComponent()
{
}

bool MovementComponent::isAFK()
{
	/*printf("time not moved: %f\n", timeNotMoved);*/
	if (timeNotMoved > 5) return true;

	return false;
}


//not in use mybe later
const bool MovementComponent::getStates(const short unsigned state)
{
	switch (state)
	{

	case 1 :   
		if (velocity.y < 0)
		{
			lastState = state;
			return true;
		}
		break;
	case 2:
		if (velocity.y > 0)
		{
			lastState = state;
			return true;
		}
		break;
	case 3:
		if (velocity.x < 0)
		{
			lastState = state;
			return true;
		}
		break;
	case 4:
		if (velocity.x > 0)
		{
			lastState = state;
			return true;
		}
		break;
	case 5:
	
		if (!(this->velocity.x + this->velocity.y) > 0) //wenn nichtb bewgt und letzter state hoch gehen war dann ist		
		{
			
			return true;
		}
		break;
	
	default: break;

	}

	/*printf("velox: %f veloy: %f\n", velocity.x, velocity.y);*/

	return false;
}

sf::FloatRect MovementComponent::getGlobalBounds() const
{
	return ptrAnimation->getSprite().getGlobalBounds();
}

void MovementComponent::resetOldPos()
{
	oldPosition = currentPosition;
}



const sf::Vector2f & MovementComponent::getVelocity(float multiplier) const
{
	return (this->velocity*multiplier);
}



const sf::Vector2f & MovementComponent::getPosition() const
{	
	return currentPosition;
}

const sf::Vector2f & MovementComponent::getOldPosition() const
{
	return oldPosition;
}

const float MovementComponent::getMaxVelocity()
{
	return maxVelocity;
}

const float MovementComponent::getAngleToTarget(sf::Vector2f target)
{
	float a = atan2(target.y - getPosition().y, target.x - getPosition().x);
	a *= (180 / M_PI);

	return a;
}

const sf::Vector2i & MovementComponent::getPosAsFieldNumber(unsigned int tilesize)
{
	return sf::Vector2i(currentPosition.x/tilesize, currentPosition.y/tilesize);
}

float MovementComponent::getDistanceToTarget(sf::Vector2f target)
{
	float xd = target.x - getPosition().x;
	float yd = target.y - getPosition().y;
	float ergebnis = sqrt((xd * xd) + (yd * yd));
	return ergebnis;
}

void MovementComponent::moveToTarget(const sf::Vector2f & targetPos)
{
	//sf::Vector2f velocity;
	//sf::Vector2f dir;

	//dir.x = (enemypos.x - x);
	//dir.y = (enemypos.y - y);

	////pytahogars
	//float factor = (6.01 / (sqrt((dir.x*dir.x) + (dir.y*dir.y))));

	//velocity.x = (dir.x / factor);



	//velocity.y = (dir.y / factor); //faktor wird hier nur f+r doe geschwinmdigkeit gebraucht

	//x += velocity.x;
	//y += velocity.y;
}

//template mit sfvector nnochmachen
void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{

	//beschleunige a sprite bis es seine max geschw. erreicht

	//Accelaration -> beschleunigung
	

	this->velocity.x += this->acceleration*dir_x;
	this->velocity.y += this->acceleration*dir_y;



}

void MovementComponent::move(const sf::Vector2f velo)
{

	//beschleunige a sprite bis es seine max geschw. erreicht

	//Accelaration -> beschleunigung

	this->velocity.x += this->acceleration*velo.x;
	this->velocity.y += this->acceleration*velo.y;


}


//
void MovementComponent::moveWithoutAcceleration(const sf::Vector2f velo)
{
	/*this->velocity.x += velo.x;
	this->velocity.y += velo.y;*/
	this->ptrAnimation->move(velo);
	
}

void MovementComponent::pushToRight(float factor)
{
	velocity.x = maxVelocity*factor;
}

void MovementComponent::pushToLeft(float factor)
{
	velocity.x = -maxVelocity * factor;
}

//mike litoris
void MovementComponent::moveRandom()
{

	int random = rand() % + 16;

	int x = random & 1;
	int y = random & 3;

	if (x == 1)
	{
		 random = rand() % +16;

		 if(random>7)
			x *= -1;
	}

	this->velocity.x += this->acceleration*x;
	this->velocity.y += this->acceleration*y;
}


void MovementComponent::setOldPosition()
{
	if (ptrAnimation)
	ptrAnimation->setPosition(oldPosition);

	currentPosition = oldPosition;
	velocity = sf::Vector2f(0.f, 0.f);
	isColliding = false;

}

void MovementComponent::setPosition(const sf::Vector2f &pos, bool resetOldPos)
{
	if (ptrAnimation)
	ptrAnimation->setPosition(pos);


	currentPosition = pos;
}

void MovementComponent::changeAttributs(float maxVelo, float acceleration, float decceleration)
{
	this->maxVelocity = maxVelo;
	this->acceleration = acceleration;
	this->decelaration = decceleration;
}

void MovementComponent::update(const float & dt)
{
	//verzögerung bzw. abbremsen nachdem nichts mehr
	//gedrückt wird, also es wird auch abgebremst wenn 
	//velocity inkrementiert wird aber beschleunigung
	//muss mehr sein als bremesen sonst bleib spieler stehen

	

	if (!freezeVelo)
	{

		if (this->velocity.x > 0.f) //spieler läuft nach rechts
		{
			//wir paSSEN auf das wir unsere maxgeschw.
			//nicht ueberschreiten
			if (this->velocity.x > this->maxVelocity)
				velocity.x = maxVelocity;

			//wenn nichtss gedruckt wird dann bekommt velocity
			//auch nichts mehr dazu, dann wird die velocity langsam
			//reduziert bis sie letzendlich wieder 0 ist
			this->velocity.x -= decelaration;

			if (this->velocity.x < 0.f)
				velocity.x = 0.f;

		}
		else if (this->velocity.x < 0.f) //spieler läuft nach links
		{
			if (this->velocity.x < -this->maxVelocity)//oder *(-1) oder abs
				velocity.x = -maxVelocity;

			this->velocity.x += decelaration;

			if (this->velocity.x > 0.f)
				velocity.x = 0.f;
		}

		if (this->velocity.y < 0.f) //spieler läuft nach oben
		{
			if (this->velocity.y < -this->maxVelocity)
				velocity.y = -maxVelocity;

			this->velocity.y += decelaration;

			if (this->velocity.y > 0.f)
				velocity.y = 0.f;
		}
		else if (this->velocity.y > 0.f) //spieler läuft nach unten
		{
			if (this->velocity.y > this->maxVelocity)
				velocity.y = maxVelocity;

			this->velocity.y -= decelaration;
			if (this->velocity.y < 0.f)
			{
				velocity.y = 0.f;

			}
		}

	}
	else {
	

		velocity = sf::Vector2f(0, 0);

	}
	//final move
	
	if (!isColliding)
	{
		oldPosition = currentPosition;
		
		this->ptrAnimation->move(this->velocity*dt); //bewegt letzendlich character

		currentPosition = sf::Vector2f(ptrAnimation->getSprite().getPosition());
	}
	else
	{
		setOldPosition();
	
	}
	
	


	if (oldPosition != currentPosition) timeNotMoved = 0.f;
	else  timeNotMoved += dt;

}

bool MovementComponent::isStanding()
{
	if(velocity.x==0 && velocity.y ==0)
	{
	
		return true;
	}


	return false;
}

//wird benötigt um sich aus dem derzeitigen angle ein bewegungsvektor zu errechen
float MovementComponent::RADIANT = 0.017453f;


/*
dx = cos(angle*RADIANT) * speed; //bei 0 also nach rechts kommt hier cos =1 raus
dy = sin(angle*RADIANT) * speed; //hier kommt bei angle 0, also sin 0 = 0 raus deswegen nach rechts
x += dx;
y += dy;


*/