#include "EntityHandler.h"





EntityHandler::EntityHandler(AssetManager & am, SoundHandler &sh, Player * ptrPlayer, sf::RenderWindow *ptrWindow)
{
	ptrAssetManager = &am;
	this->ptrPlayer = ptrPlayer;
	terrain = std::make_shared<DestructibleTerrain>(ptrWindow);
	this->ptrWindow = ptrWindow;
	this->ptrSoundHandler = &sh;
}

EntityHandler::~EntityHandler()
{
	cleanEnemys();
}

void EntityHandler::popBullet(sf::Vector2f &spawnPos)
{

	Bullet bullet(spawnPos, Bullet::Direction::DOWN, 10.f);
	bullet.setScreenBounds(sf::Vector2i(ptrWindow->getSize().x, ptrWindow->getSize().y));
	bullets.push_back(bullet);
	ptrSoundHandler->playSound("pew");

		
}

void EntityHandler::popPlayerBullet()
{
	if (ptrPlayer->isAlive())
	{
		Bullet bullet(ptrPlayer->getMovementptr()->getPosition(), Bullet::Direction::UP, 10.f);
		bullet.setScreenBounds(sf::Vector2i(ptrWindow->getSize().x, ptrWindow->getSize().y));
		bullet.setPlayerBullet();
		bullets.push_back(bullet);
		ptrSoundHandler->playSound("pew");

	}
}

void EntityHandler::popEnemy(sf::Vector2f spawnPos,  float steptime,  float timeforspeedup)
{


	enemys.push_back(new Enemy(ptrAssetManager->GetTexture("enemy1"), sf::Vector2f(spawnPos.x, spawnPos.y),
		sf::FloatRect(0, 0, ptrWindow->getSize().x, ptrWindow->getSize().y), steptime, timeforspeedup));
}

void EntityHandler::popEnemyRows(sf::Vector2f startPos, unsigned short AmountPerRow, unsigned short rows)
{
	short enemycount = AmountPerRow * rows;

	for (int i = 0; i < enemycount; i++) {
		
		int tu = i % AmountPerRow;
		int tv = i / AmountPerRow;

		sf::Vector2f finalPos = sf::Vector2f(static_cast<float>(startPos.x + tu*80),
			static_cast<float>(startPos.y + tv*70));

		popEnemy(finalPos,.8f,static_cast<float>(MAXLEVEL-currentLevel));
				
	}
}

void EntityHandler::draw(sf::RenderTarget & target)
{

	for (auto& i : bullets)
		i.draw(target);

	for (auto& j : enemys)
		j->draw(target);


	terrain->draw(target);
	
}

void EntityHandler::update(sf::Time elapsed)
{

	enemyRoundTime += elapsed.asSeconds();


	checkforNewEnemys();

	terrain->checkAllVertexCollideWithBullets(bullets);

	updateBullets(elapsed);
	updateEnemys(elapsed);

	checkCollsionsBulletswithEnemys();
	cleanEnemysifDead();

}

void EntityHandler::updateEnemys(sf::Time elapsed)
{


	enemyBulletTimer += elapsed;
	if (enemyBulletTimer.asSeconds() > enemyBulletshotTime)
	{
		pushEnemybullet();
		enemyBulletTimer = enemyBulletTimer.Zero;
	}

	
	for (auto& e : enemys)
	{

		e->update(elapsed);
		

		if (e->checkForScreenBounds())
		{
	
			changeDirectionAllEnemys();
			
		}
			
	}
	
}

void EntityHandler::checkCollsionsBulletswithEnemys()
{
	for (auto &i : bullets)
	{
		for (auto &j : enemys)
		{
			if (j->getMovementptr()->getGlobalBounds().intersects
			(i.shape.getGlobalBounds())&&i.bisPlayerBullet)
			{
				j->kill();
				i.kill();
				
			}
		}
			
		if (i.shape.getGlobalBounds().intersects(
			ptrPlayer->getMovementptr()->getGlobalBounds())
			&&!i.bisPlayerBullet)
		{
			ptrPlayer->drawOneLife();
			i.kill();
		}
	}
}

void EntityHandler::updateBullets(sf::Time elapsed)
{

	for (int i = 0; i < bullets.size();)
	{
		bullets[i].update(elapsed);
		if (!bullets[i].isAlive())
		{
			bullets.erase(bullets.begin() + i);
			printf("kulgel gelöscht\n");
		}
		else i++;
	}

}

void EntityHandler::checkforNewEnemys()
{
	if (enemys.size() < 1)
	{

		if (currentLevel <= MAXLEVEL)
		{
			currentLevel++;
			popEnemyRows(sf::Vector2f(40, 40), 10, 5);
		}

	}
}

void EntityHandler::pushEnemybullet()
{	
	if (enemys.size() < 1)return;

	unsigned int randomenemy = std::rand() % enemys.size()+0;
	sf::FloatRect collRect = enemys[randomenemy]->getMovementptr()->getGlobalBounds();
	collRect.top += collRect.height+10;
	for (int i = 0; i < enemys.size(); i++) {
		
		if (enemys[i]->getMovementptr()->getGlobalBounds().intersects(collRect))
		{
			printf("gegner vor gegner der schiessen wollten\n");
			return;
		}
		
			
	}

	popBullet(sf::Vector2f(collRect.left, collRect.top));
}

void EntityHandler::cleanEnemysifDead()
{
	for (auto& i = enemys.begin(); i != enemys.end();)
	{
		Enemy *ptrCurrentEnemy = *i;

		if (!ptrCurrentEnemy->isAlive())
		{
			delete ptrCurrentEnemy;
			i = enemys.erase(i);
			ptrSoundHandler->playSound("explosion");
			ptrPlayer->inkrementPoints();
		}
		else {
			i++;
		}
	}
}

void EntityHandler::cleanEnemys()
{
	for (auto& i = enemys.begin(); i != enemys.end();i++)
	{
		Enemy *ptrCurrentEnemy = *i;
		delete ptrCurrentEnemy;
		
	
		
	}
	enemys.clear();
}

void EntityHandler::changeDirectionAllEnemys()
{
	for (auto& e : enemys)
	{
		e->getMovementptr()->setOldPosition();
		e->StepDown();
		e->changeDirection();
		
		
	}
}
