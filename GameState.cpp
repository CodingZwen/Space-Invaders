#include "GameState.h"



GameState::GameState(sf::RenderWindow *ptrWindow,   AssetManager &AM, SoundHandler &SH)
{

	this->ptrWindow = ptrWindow;
	int startposx = ptrWindow->getSize().x / 2;
	int startposy = ptrWindow->getSize().y-
				   (ptrWindow->getSize().y / 10);


	playertex.loadFromFile("resources\\playertex.png");
	player = new Player(playertex,sf::Vector2f(startposx, startposy));
	player->setScreenBounds(sf::Vector2i(ptrWindow->getSize().x, ptrWindow->getSize().y));
	ptrAssetManager = &AM;

	
	eh = std::make_shared<EntityHandler>(AM, SH, player, ptrWindow );

	txtCurrentPoints.setFont(*AM.ptr_GetFont("font"));
	txtCurrentPoints.setCharacterSize(20.f);
	txtCurrentPoints.setFillColor(sf::Color::White);
	txtCurrentPoints.setPosition(sf::Vector2f(10, 10));

	eh->popEnemyRows(sf::Vector2f(40, 40), 10, 5);

	

}


GameState::~GameState()
{
}

void GameState::HandleEvents(Game & game)
{
	sf::Event e;
	while (game.window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			game.window.close();
			game.stopRunning();
		}


		if (e.type == sf::Event::KeyPressed) {


			if (e.key.code == sf::Keyboard::Escape) {

				game.changeState(Game::GameInstances::Startmenuestate);
			}

			if (e.key.code == sf::Keyboard::Delete) {

			
			}



			if (e.key.code == sf::Keyboard::Space) {

				eh->popPlayerBullet();
				eh->pushEnemybullet();
			
				
			}
		}


		updatePlayer(e,game.frameDeltaTime,1);

	}
}

void GameState::Update(Game & game)
{
	std::string s= "Highscore: ";
	s += std::to_string(player->getPoints());
	txtCurrentPoints.setString(s);


	eh->update(game.frameDeltaTime);
	
	player->update(game.frameDeltaTime);
}

void GameState::Draw(Game & game)
{
	eh->draw(game.window);
	player->draw(game.window);

	game.window.draw(txtCurrentPoints);


	if (player->isAlive())
	{
		for (int i = 0; i < player->getLives(); i++) {
			sprPlayerlives = player->getSprite();
			sprPlayerlives.setPosition(sf::Vector2f(40 + i * 80, game.window.getSize().y - 20));
			game.window.draw(sprPlayerlives);
		}
	}
	else {
		sprPlayerlives = player->getSprite();
		sprPlayerlives.setPosition(sf::Vector2f(40, game.window.getSize().y - 20));
		game.window.draw(sprPlayerlives);
	}


}

void GameState::updatePlayer(sf::Event e,sf::Time elapsed,bool withAcceleration)
{
	if (e.type == sf::Event::KeyPressed) {

		if (e.key.code == sf::Keyboard::A || e.key.code == sf::Keyboard::Left) {
			if(withAcceleration)
			player->getMovementptr()->move(sf::Vector2f(-1, 0));
			else player->getMovementptr()->moveWithoutAcceleration(sf::Vector2f(-1000, 0));
		}
		else if (e.key.code == sf::Keyboard::D || e.key.code == sf::Keyboard::Right) {
			if (withAcceleration)
			player->getMovementptr()->move(sf::Vector2f(1, 0));
			else player->getMovementptr()->moveWithoutAcceleration(sf::Vector2f(1000, 0));
		}
		else if (e.key.code == sf::Keyboard::W || e.key.code == sf::Keyboard::Up) {
			if (withAcceleration)
				player->getMovementptr()->move(sf::Vector2f(0, -1));
			else player->getMovementptr()->moveWithoutAcceleration(sf::Vector2f(0, -1000));
		}
		else if (e.key.code == sf::Keyboard::S || e.key.code == sf::Keyboard::Down) {
			if (withAcceleration)
				player->getMovementptr()->move(sf::Vector2f(0, 1));
			else player->getMovementptr()->moveWithoutAcceleration(sf::Vector2f(0,1000));
		}
		
		
	}//hier hört keypress auf
}

