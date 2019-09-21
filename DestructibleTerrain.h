#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include  "Bullet.h"
#include <array>
#include "Quadtree.h"
class DestructibleTerrain
{

	sf::RenderWindow *ptrWindow;
	std::vector<sf::VertexArray> walls;
	std::vector<std::vector<sf::RectangleShape>> cheaperWalls;



	void checkVertexCollideWithBullets(std::vector<Bullet> &bullets, sf::VertexArray &vertices);


public:
	DestructibleTerrain(sf::RenderWindow *ptrWindow);
	~DestructibleTerrain();


	void pushWall(unsigned short count);
	void pushCheaperWall(unsigned short count, float sizePerBlock);
	void draw(sf::RenderTarget &target);
	void update(sf::Time elapsed);
	void checkCollide(sf::FloatRect collRect,sf::VertexArray &vertexarray);
	void checkAllVertexCollideWithBullets(std::vector<Bullet> &bullets);
	

	void kill();

	inline 	bool isCollide(sf::Vector2f particlePos, sf::CircleShape &shape) {

		return (shape.getPosition().x - particlePos.x)*(shape.getPosition().x - particlePos.x) +
			(shape.getPosition().y - particlePos.y)*(shape.getPosition().y - particlePos.y) <
			(0.5f + shape.getRadius())*(0.5f + shape.getRadius());

	}




};

