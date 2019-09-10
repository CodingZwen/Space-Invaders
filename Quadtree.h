#pragma once
#include <SFML/Graphics.hpp>


//wird benutzt um infor über einen punkt zu halten


class Quadtree
{
	static int dividedCount;

	unsigned short capacity;
	bool divided;
	std::vector<sf::Vector2f> points;
	std::vector<sf::Vertex*> ptrVertices;

	sf::FloatRect motherQuad;
	sf::RectangleShape rect;


	Quadtree* nw;
	Quadtree* ne;
	Quadtree* sw;
	Quadtree* se;

	void checkCollide();
	inline bool particleCollsion(const sf::Vector2f &particle1,const  sf::Vector2f &particle2);

	
public:
	Quadtree(sf::FloatRect quad,unsigned short capacity =80);

	~Quadtree();

	bool isDivided() { return divided; };
	bool pushPoint(sf::Vector2f point,sf::Vertex*v=nullptr);
	void pushPoints(std::vector<sf::Vector2f>& points);
	void pushVerticesPtr( sf::VertexArray &vertexarray);

	void subdivide();
	void draw(sf::RenderTarget &target);
	

	void cleanUp();

	std::vector<sf::Vector2f> query(sf::FloatRect&);
	void fillVecwithPoints(std::vector<sf::Vector2f> &vecToFill, sf::FloatRect pointBox);

};

