#include "DestructibleTerrain.h"



DestructibleTerrain::DestructibleTerrain(sf::RenderWindow *ptrWindow)
{
	this->ptrWindow = ptrWindow;
	pushWall(4);
	//pushCheaperWall(4,10);

	
}


DestructibleTerrain::~DestructibleTerrain()
{
}



void DestructibleTerrain::pushWall(unsigned short count)
{
	short amount = count;

	sf::VertexArray m_vertices;
	sf::Vector2f spawnPosition = sf::Vector2f(100, ptrWindow->getSize().y- (ptrWindow->getSize().y/3));
	int pixels = 3300;
	float gapBetwenWalls = 300;
	m_vertices = sf::VertexArray(sf::Points, pixels);


	for (int i = 0; i < pixels; i++) {


		int tu = i % 110; //sobald i zahl erreicht wird von vorne gemalt
		int tv = i / 110; //sobald i zahl erreicht wird ein schritt runter weiter gemalt

		sf::Vector2f finalPos = sf::Vector2f(static_cast<float>(spawnPosition.x + tu),
			static_cast<float>(spawnPosition.y + tv));

		sf::Vertex *vertex = &m_vertices[i];
		vertex->position = finalPos;
		vertex->color = sf::Color::Green;

		/*printf("tu: %d an pos gesetzt: x: %f y: %f\n",tu, vertex->position.x+tu, vertex->position.y+tv);
		printf("ohne tu x: %f y: %f\n", vertex->position.x , vertex->position.y );
*/
	}
	walls.push_back(m_vertices);

	while (--amount > 0)
	{
		for (int i = 0; i < pixels; i++) {


			sf::Vertex *vertex = &m_vertices[i];
			vertex->position.x += gapBetwenWalls;
			/*printf("tu: %d an pos gesetzt: x: %f y: %f\n",tu, vertex->position.x+tu, vertex->position.y+tv);
			printf("ohne tu x: %f y: %f\n", vertex->position.x , vertex->position.y );
	*/
		}

		walls.push_back(m_vertices);
	}
}

void DestructibleTerrain::pushCheaperWall(unsigned short count,float sizePerBlock)
{
	short amount = count;

	
	std::vector<sf::RectangleShape> wall;
	sf::Vector2f spawnPosition = sf::Vector2f(100, ptrWindow->getSize().y - (ptrWindow->getSize().y / 3));
	sf::RectangleShape rect;
	int blocks = 30;
	float gapBetwenWalls = 300;
	


	for (int i = 0; i < blocks; i++) {


		int tu = i % 10; //sobald i zahl erreicht wird von vorne gemalt
		int tv = i / 10; //sobald i zahl erreicht wird ein schritt runter weiter gemalt

		sf::Vector2f finalPos = sf::Vector2f(static_cast<float>(spawnPosition.x +
			(tu* sizePerBlock)),
			static_cast<float>(spawnPosition.y + (tv* sizePerBlock)));
		rect.setOutlineThickness(1.f);
		rect.setOutlineColor(sf::Color::Magenta);
		rect.setPosition(finalPos);
		rect.setFillColor(sf::Color::Green);
		rect.setSize(sf::Vector2f(sizePerBlock, sizePerBlock));

		wall.push_back(rect);

		/*printf("tu: %d an pos gesetzt: x: %f y: %f\n",tu, vertex->position.x+tu, vertex->position.y+tv);
		printf("ohne tu x: %f y: %f\n", vertex->position.x , vertex->position.y );
*/
	}
	cheaperWalls.push_back(wall);

	while (--amount > 0)
	{
		std::vector<sf::RectangleShape> rectBuffer;

		for (int i = 0; i < blocks; i++) {


			
			wall[i].setPosition((wall[i].getPosition().x+gapBetwenWalls),
				wall[i].getPosition().y);

			rectBuffer.push_back(wall[i]);
			/*printf("tu: %d an pos gesetzt: x: %f y: %f\n",tu, vertex->position.x+tu, vertex->position.y+tv);
			printf("ohne tu x: %f y: %f\n", vertex->position.x , vertex->position.y );
	*/
		}

		cheaperWalls.push_back(rectBuffer);
		std::cout << "bloecke reingemacht: " << rectBuffer.size() << std::endl;
	}
}

void DestructibleTerrain::draw(sf::RenderTarget & target)
{

	for (const auto &i : walls)
		target.draw(i);

	for (auto &i : cheaperWalls)
	{
		for (auto &j : i)
		{
			target.draw(j);
		}
	}

}


void DestructibleTerrain::checkCollide(sf::FloatRect collRect, sf::VertexArray &vertexarray)
{
	for (int i = 0; i < vertexarray.getVertexCount(); i++) {
	
		sf::Vertex *vertex = &vertexarray[i];
		if (collRect.intersects(sf::FloatRect(vertex->position.x,vertex->position.y,1,1)))
		{
			//printf("collision");
		}
	
	}
}


void DestructibleTerrain::checkAllVertexCollideWithBullets(std::vector<Bullet>& bullets)
{


	for (auto &i : walls)
	{
		checkVertexCollideWithBullets(bullets, i);
	
	}



}

void DestructibleTerrain::checkVertexCollideWithBullets(std::vector<Bullet>& bullets, sf::VertexArray & vertices)
{
	
	for (int i = 0; i < bullets.size(); i++)
	{

		for (int j = 0; j < vertices.getVertexCount(); j++) {

			sf::Vertex *vertex = &vertices[j];

			
			if (bullets[i].shape.getGlobalBounds().intersects(
				sf::FloatRect(vertex->position.x, vertex->position.y, 1, 1))
				&& vertex->color.a > 1)
			{
				sf::CircleShape collShape(10);
				collShape.setPosition(vertex->position);

				for (int k = 0; k < vertices.getVertexCount(); k++) {
					vertex = &vertices[k];

					if (isCollide(vertex->position, collShape))
					{
						vertex->color.a=0;

					}

				}
				bullets[i].kill();

			}


		}
	}

}

void DestructibleTerrain::kill()
{
}



/*
for (int i = 0; i < vertices.getVertexCount(); i++) {

		sf::Vertex *vertex = &vertices[i];

		sf::FloatRect collRect;

		for (int j = 0; j < bullets.size(); j++)
		{
			collRect = bullets[j].shape.getGlobalBounds();
			if (collRect.intersects(sf::FloatRect(vertex->position.x, vertex->position.y, 1, 1))
				&& vertex->color.a > 1)
			{


				collShape.setPosition(vertex->position);

				for (int k = 0; k < vertices.getVertexCount(); k++) {
					sf::Vertex *cvertex = &vertices[k];

					if (isCollide(cvertex->position, collShape))
					{
						cvertex->color = sf::Color(0, 0, 0, 0);


					}

				}
				bullets.erase(bullets.begin() + j);

			}
		}



	}
*/