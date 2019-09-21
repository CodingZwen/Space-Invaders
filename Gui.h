#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Gui
{
	bool multiplayer;
	sf::Text txtCurrentPointsPlayer1;
	sf::Text txtCurrentPointsPlayer2;
	sf::Text txtCurrentHighscore;
	Player *ptr_player1;
	Player *ptr_player2;


	/*
	TODO
	score anzeige auf bildschirm anpassen
	*/

public:
	Gui();
	~Gui();

	void draw(sf::RenderTarget &target);
	void update(sf::Time elapsed);
	void init(const sf::Font &font, Player *player1,unsigned int highscore, std::string highscoreplayername,Player *player2=nullptr);

	void createPlayer1String();
	void createPlayer2String();
	void createCurrentHighscore();

};

