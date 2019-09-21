#pragma once
#include "State.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "AssetManager.h"
#include "Enemy.h"
#include "EntityHandler.h"
#include "Highscore.h"
#include "Gui.h"
class GameState : public State 
{
	unsigned int playerLives = 3;
	sf::Sprite sprPlayerlives;
	std::shared_ptr<EntityHandler> eh;
	

	Player *player;
	sf::Texture playertex;

	sf::RenderWindow *ptrWindow;
	AssetManager *ptrAssetManager;

	sf::View view;

	Gui gui;
	Highscore hs;

public:
	GameState(sf::RenderWindow *ptrWindow,  AssetManager &AM, SoundHandler &SH);
	 virtual ~GameState();


	 void HandleEvents(Game &game);
	 void Update(Game &game);
	 void Draw(Game &game);

	 void updatePlayer(sf::Event e, sf::Time elapsed, bool withAcceleration = true);
	
	 //oberklasse Gui erzeugen, 
	 //obergläche mit punkte, leben , current highscore
	 void updateOverlayInterface(sf::Time elapsed);

	// std::vector<Bullet>bullets;
	
};

