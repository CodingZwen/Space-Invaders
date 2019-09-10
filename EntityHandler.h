#pragma once
#include <map>
#include "Bullet.h"
#include "AssetManager.h"
#include "DestructibleTerrain.h"
#include "SoundHandler.h"
#include "Quadtree.h"
#include "Player.h"
#include "Enemy.h"




class EntityHandler
{
	const int MAXLEVEL = 16;
	unsigned int currentLevel = 1;
	
	float LevelReduceTime = 20.f;


	sf::Time enemyBulletTimer;


	float enemyBulletshotTime =0.6f; //not exactly it dont do anything if enemy in front of him

	float enemyRoundTime;

	std::shared_ptr<DestructibleTerrain> terrain;
	std::shared_ptr<Quadtree> qt;
	sf::RenderWindow *ptrWindow;
	AssetManager *ptrAssetManager;
	SoundHandler *ptrSoundHandler;
	//for handling bullets
	std::vector<Bullet> bullets;
	//to check with bullets -> all enemys
	std::vector<Enemy*> enemys;

	Player *ptrPlayer;

public:
	EntityHandler(AssetManager &am,SoundHandler &sh, Player *ptrPlayer, sf::RenderWindow *ptrWindow);
	~EntityHandler();

	void popBullet(sf::Vector2f &spawnPos);
	void popPlayerBullet();
	void popEnemy(sf::Vector2f spawnPos,float steptime,float timeforspeedup);
	void popEnemyRows(sf::Vector2f startPos,unsigned short AmountPerRow, unsigned short rows);
	void draw(sf::RenderTarget &target);
	void update(sf::Time elapsed);

	void updateEnemys(sf::Time elapsed);
	void checkCollsionsBulletswithEnemys();
	void updateBullets(sf::Time elapsed);
	void updateObstacles(sf::Time elapsed);
	void checkforNewEnemys();

	void pushEnemybullet();

	//cleaner
	void cleanEnemysifDead();
	void cleanEnemys();
	void cleanBullets() { bullets.clear(); }

	void changeDirectionAllEnemys();

};

