#include "Gui.h"



Gui::Gui()
	: multiplayer(0)
{
	
}


Gui::~Gui()
{
}

void Gui::draw(sf::RenderTarget & target)
{
	target.draw(txtCurrentPointsPlayer1);

	target.draw(txtCurrentPointsPlayer2);

}

void Gui::update(sf::Time elapsed)
{
	createPlayer1String();

	if(multiplayer)
		createPlayer2String();
}

void Gui::init(const sf::Font & font, Player *player1,  unsigned int highscore, std::string highscoreplayername, Player *player2)
{
	txtCurrentPointsPlayer1.setFont(font);
	txtCurrentPointsPlayer1.setCharacterSize(20.f);
	txtCurrentPointsPlayer1.setFillColor(sf::Color::White);
	txtCurrentPointsPlayer1.setPosition(sf::Vector2f(10, 10));

	txtCurrentPointsPlayer2.setFont(font);
	txtCurrentPointsPlayer2.setCharacterSize(20.f);
	txtCurrentPointsPlayer2.setFillColor(sf::Color::White);
	txtCurrentPointsPlayer2.setPosition(sf::Vector2f(10+1000, 10)); //hier muss noch auf fenster angepasst werden

	ptr_player1 = player1;


	if (player2)
	{
		multiplayer = true;	
		ptr_player2 = player2;
	}
	else {
		std::string s = "Score<2> ";
		txtCurrentPointsPlayer2.setString(s);
	}


}

void Gui::createPlayer1String()
{
	std::string s = "Score<1> ";
	s += std::to_string(ptr_player1->getPoints());
	txtCurrentPointsPlayer1.setString(s);
}

void Gui::createPlayer2String()
{
	std::string s = "Score<2>: ";
	s += std::to_string(ptr_player2->getPoints());
	txtCurrentPointsPlayer2.setString(s);
}
