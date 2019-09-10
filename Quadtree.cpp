#include "Quadtree.h"



void Quadtree::checkCollide()
{
	if (points.size() < 1)return;

	for (int i = 0; i < points.size(); i++)
	{

		for (int j = i+1; j < points.size(); j++)
		{
			if (particleCollsion(points[i], points[j]))
			{
				ptrVertices[i]->color = sf::Color::Blue;
				ptrVertices[j]->color = sf::Color::Blue;
				rect.setOutlineColor( sf::Color::Red);
				
			}
			
		}
	}

}

bool Quadtree::particleCollsion(const sf::Vector2f &particle1,const  sf::Vector2f &particle2)
{
	return particle1.x == particle2.x && particle1.y == particle2.y ? true: false;
}

Quadtree::Quadtree(sf::FloatRect quad, unsigned short capacity)
{
	this->capacity = capacity;
	this->points.reserve(capacity);
	this->ptrVertices.reserve(capacity);
	motherQuad = quad;
	divided = false;
	rect.setSize(sf::Vector2f(quad.width, quad.height));
	rect.setPosition(quad.left, quad.top);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	//rect.setOutlineColor(sf::Color(235,52,222,50));
	rect.setOutlineColor(sf::Color(255, 255, 255, 10));
	rect.setOutlineThickness(1.0f);


	


	this->nw = nullptr;
	this->ne = nullptr;
	this->sw = nullptr;
	this->se = nullptr;

}


Quadtree::~Quadtree()
{

	dividedCount = 0;

	if (nw) {
		
		delete nw; 
	}
	if (ne) {
		
		delete ne;
	}
	if (sw) {
		
		delete sw;
	}

	if (se) {
		
		delete se;
	}
	

}

bool Quadtree::pushPoint(sf::Vector2f point,sf::Vertex* vptr)
{
	if (!motherQuad.contains(point)) { return false; }

	if (points.size() < capacity)
	{
		points.push_back(point);
	
		if (vptr)ptrVertices.push_back(vptr);

		
		checkCollide();
		//wen punkt erfolgreich reingemacht
		return true;
	}
	else
	{
		if (!divided) {
			subdivide();
			
		}

		if(this->nw->pushPoint(point, vptr))return true;
		if(this->ne->pushPoint(point, vptr))return true;
		if(this->sw->pushPoint(point, vptr))return true;
		if(this->se->pushPoint(point, vptr))return true;
		else return false;
	
	}

}

void Quadtree::pushPoints(std::vector<sf::Vector2f>& points)
{
	
	for (auto &i : points)
		pushPoint(i);

}

void Quadtree::pushVerticesPtr( sf::VertexArray &vertexarray)
{
	for (int i = 0; i < vertexarray.getVertexCount(); i++)
	{
		sf::Vertex *vptr = &vertexarray[i];
		pushPoint(vptr->position, vptr);
	}
}

void Quadtree::subdivide()
{

	dividedCount++;
	

	sf::FloatRect nw = sf::FloatRect(motherQuad.left,
		motherQuad.top,
		motherQuad.width / 2,
		motherQuad.height / 2);

	this->nw = new Quadtree(nw);
	
	sf::FloatRect ne = sf::FloatRect(motherQuad.left + motherQuad.width / 2,
		motherQuad.top,
		motherQuad.width / 2,
		motherQuad.height / 2);


	this->ne = new Quadtree(ne);

	sf::FloatRect sw = sf::FloatRect(motherQuad.left + motherQuad.width / 2,
		motherQuad.top + motherQuad.height / 2,
		motherQuad.width / 2,
		motherQuad.height / 2);

	this->sw = new Quadtree(sw);

	sf::FloatRect se = sf::FloatRect(motherQuad.left,
		motherQuad.top + motherQuad.height / 2,
		motherQuad.width / 2,
		motherQuad.height / 2);

	this->se = new Quadtree(se);

	divided = true;
}



void Quadtree::draw(sf::RenderTarget & target)
{
	target.draw(rect);

	/*if(vpoints.size()>0)target.draw(&vpoints[0], vpoints.size(), sf::Points);*/

	if (this->nw)nw->draw(target);
	if (this->ne)ne->draw(target);
	if (this->sw)sw->draw(target);
	if (this->se)se->draw(target);

}

void Quadtree::cleanUp()
{


}

std::vector<sf::Vector2f> Quadtree::query(sf::FloatRect &collRect)
{
	std::vector<sf::Vector2f> foundPoints;
	foundPoints.reserve(2048);

	


	if (!this->motherQuad.intersects(collRect))
	{
		return foundPoints;
	}
	else {

		fillVecwithPoints(foundPoints, collRect);


		if (this->divided)
		{
			std::vector<sf::Vector2f> buffer = this->nw->query(collRect);
			foundPoints.insert(foundPoints.end(), buffer.begin(), buffer.end());

			buffer = this->ne->query(collRect);
			foundPoints.insert(foundPoints.end(), buffer.begin(), buffer.end());

			buffer = this->sw->query(collRect);
			foundPoints.insert(foundPoints.end(), buffer.begin(), buffer.end());

			buffer = this->se->query(collRect);
			foundPoints.insert(foundPoints.end(), buffer.begin(), buffer.end());

			
		}
		
		return foundPoints;
	}



}

void Quadtree::fillVecwithPoints(std::vector<sf::Vector2f>& vecToFill,sf::FloatRect pointBox)
{
	for (auto &i : points)
	{
		if (pointBox.contains(i))
		vecToFill.push_back(i);
	}
}

int Quadtree::dividedCount = 0;


/*
	
	std::vector<sf::Vector2f> foundPoints;

	system("cls");


	if (!this->motherQuad.intersects(collRect))
	{
		printf("wollte returnrn \n");
		printf("groessepoints bei nichtintersect: %d\n", points.size());
		return foundPoints;
	}
	else {

		

		for (auto i : points) {

			printf("groessefound: %d\n",foundPoints.size());
			printf("groessepoints: %d\n", points.size());

			if(collRect.contains(i))
			foundPoints.push_back(i);
			
		}

		if (this->divided)
		{
			printf("ist dividde\n");

			if (nw->points.size() > 0)
			{
				foundPoints.insert(foundPoints.end(),
					this->nw->query(collRect).begin(), this->nw->query(collRect).end());

				printf("groesse nw: %d\n", nw->points.size());
			}

			if (ne->points.size() > 0)
			{
				foundPoints.insert(foundPoints.end(),
					this->ne->query(collRect).begin(), this->ne->query(collRect).end());

				printf("groesse ne: %d\n", ne->points.size());
			}

			if (sw->points.size() > 0)
			{
				foundPoints.insert(foundPoints.end(),
					this->sw->query(collRect).begin(), this->sw->query(collRect).end());
				printf("groesse sw: %d\n", sw->points.size());
			}

			if (se->points.size() > 0)
			{
				foundPoints.insert(foundPoints.end(),
					this->se->query(collRect).begin(), this->se->query(collRect).end());
				printf("groesse se: %d\n", se->points.size());
			}

			printf("groessepoints bei divided: %d\n", points.size());
		}
		printf("gefundene punkte vorm returnen: %d\n", foundPoints.size());
		printf("groessepoints bei returnen: %d\n", points.size());
		return foundPoints;
	}



*/