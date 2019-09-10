#pragma once
#include "State.h"
#include "Game.h"
#include "Button.h"
class StartMenue : public State 
{
private :

	std::map<std::string, std::shared_ptr<Button>> shareptr_Buttons;
	Button *ptrCurrentButton;
	Button *ptrLastButton;
	sf::Font *font = nullptr;
	
public:
	StartMenue(sf::Font *f, sf::Vector2i screenDimensions);
	~StartMenue();

	void initButtons(sf::Vector2i screenDimensions, short charSize =12);

	 void HandleEvents(Game &a);
	 void Update(Game &a);
	 void Draw(Game &a);

	 void RenderButtons(sf::RenderTarget &target);
	 void updateButtons(Game &game);


};

