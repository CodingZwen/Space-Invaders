#pragma once

class Game;
	
class State
{
public:
	State();
		
	virtual	~State();
	virtual void HandleEvents(Game &a) = 0;
	virtual void Update(Game &a) = 0;
	virtual void Draw(Game &a) = 0;
};

