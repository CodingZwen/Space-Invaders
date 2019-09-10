#include "StartMenue.h"



StartMenue::StartMenue(sf::Font *font,sf::Vector2i screenDimensions)
{
	this->font = font;
	initButtons(screenDimensions);
	ptrCurrentButton = nullptr;
	ptrLastButton = nullptr;

}


StartMenue::~StartMenue()
{
}

void StartMenue::initButtons(sf::Vector2i screenDimensions, short charSize)
{


	std::cout << "screenx: " << screenDimensions.x;
	std::cout << " screeny: " << screenDimensions.y << std::endl;


	int x = screenDimensions.x / 2;
	int y = screenDimensions.y / 2;
	int width = 150;
	int height = 50;
	int verticalGap = 100;
	x -= width / 2;
	y -= height / 2;

	int helpButtonsX = 10;
	int helpButtonsY = 10;
	int helpButtonwidth = 120;
	int helpButtonheight = 50;
	int horizontalGap = 150;


	shareptr_Buttons["Start"] = std::make_shared<Button>(x, y, width, height, this->font, "Start Game", charSize,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	shareptr_Buttons["Exit"] = std::make_shared<Button>(x, y + verticalGap, width, height, this->font, "Exit Game", charSize,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));



	shareptr_Buttons["Options"] = std::make_shared<Button>(x, y + verticalGap * 2, width, height, this->font, "Options", charSize,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));


	//help buttons
	verticalGap = 0;

	shareptr_Buttons["ShowFPS"] = std::make_shared<Button>(helpButtonsX + horizontalGap * 0, helpButtonsY + verticalGap * 0, helpButtonwidth, helpButtonheight, this->font, "ShowFPS", charSize,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	shareptr_Buttons["Max40FPS"] = std::make_shared<Button>(helpButtonsX + horizontalGap * 1, helpButtonsY + verticalGap * 1, helpButtonwidth, helpButtonheight, this->font, "Max FPS Off", charSize,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	shareptr_Buttons["MaxFPS"] = std::make_shared<Button>(helpButtonsX + horizontalGap * 2, helpButtonsY + verticalGap * 2, helpButtonwidth, helpButtonheight, this->font, "Max FPS On", charSize,
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

}

void StartMenue::HandleEvents(Game & game)
{
	sf::Event e;
	while (game.window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			game.window.close();
			game.stopRunning();
		}

	}
	//achtung wenn in poll event oder darüber dann kack game ab
	this->updateButtons(game);
}

void StartMenue::Update(Game & a)
{
}

void StartMenue::Draw(Game & game)
{

	RenderButtons(game.window);
}

void StartMenue::RenderButtons(sf::RenderTarget & target)
{
	for (auto it = shareptr_Buttons.begin(); it != shareptr_Buttons.end(); ++it)
	{
		it->second->render(&target);
	}
}

//enum GameInstances { Startmenuestate, Playstate, Optionstate };

void StartMenue::updateButtons(Game &game)
{

	for (auto it = shareptr_Buttons.begin(); it != shareptr_Buttons.end(); ++it)
	{
		it->second->update(game.mousePosView,&ptrCurrentButton);
	}

	if (this->shareptr_Buttons["Start"]->isPressed())
	{
		game.changeState(Game::GameInstances::Playstate);
		printf("versucht spiel zu starten\n\n");
	}
	else if (this->shareptr_Buttons["Exit"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

		game.stopRunning();
	}
	else if (this->shareptr_Buttons["ShowFPS"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

	
	}
	else if (this->shareptr_Buttons["Max40FPS"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{

		
	}
	else if (this->shareptr_Buttons["MaxFPS"]->isPressed()) //rip wenn kein eslse if da er sonst noch Exit prüft und backackt
	{
	
	}


	if (ptrCurrentButton)
	{
		if (ptrCurrentButton != ptrLastButton)
		{
			game.soundHandler.playSound("select");
			ptrLastButton = ptrCurrentButton;
		}
			
	}

}
