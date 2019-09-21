#include "ParticleSystem.h"



ParticleSystem::ParticleSystem(unsigned int count)
	: particles(count), vertices(sf::Points,count), lifetime(sf::seconds(5.f)),
	sourcePosition(0,0)
{

	for (auto &i : particles) {
		i.rect = sf::RectangleShape(sf::Vector2f(10, 10));
		i.rect.setFillColor(sf::Color::Green);
	}

}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::resetParticle(unsigned int i, sf::Color c)
{
	float angle = (std::rand() % 360) *3.14f / 180.f;
	float speed = (std::rand() % 40) + 40;

	particles[i].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	particles[i].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
	vertices[i].color = c;// reset the position of the corresponding vertex
	vertices[i].position = sourcePosition;
	

}


void ParticleSystem::setSourcePosition(sf::Vector2f sourcepos)
{
	this->sourcePosition = sourcepos;
}

void ParticleSystem::update(sf::Time elapsed)
{



	for (size_t i = 0; i < this->particles.size(); i++)
	{
		Particle &p = particles[i];
		
		if(p.lifetime.asSeconds()>0)p.lifetime -= elapsed;

		

		// update the position of the corresponding vertex
		vertices[i].position += p.velocity * elapsed.asSeconds();
		
		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() /lifetime.asSeconds();
		particles[i].rect.setPosition(vertices[i].position);
		vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
	//checkCollideVertices();
	//checkCollideParticles();
	
}

void ParticleSystem::checkCollideVertices()
{

	for (size_t i = 0; i < this->vertices.getVertexCount(); i++)
	{
		sf::Vertex &p = vertices[i];
		
		for (size_t k = i+1; k < this->vertices.getVertexCount(); k++)
		{
			sf::Vertex &p2 = vertices[k];

			if (p.position.x == p2.position.x
				&&p.position.y == p2.position.y)
			{
				p2.color= sf::Color::Green;
				p.color = sf::Color::Green;
				
				
			}
			
		}

		// update the alpha (transparency) of the particle according to its lifetime


	}

}

void ParticleSystem::checkCollideParticles()
{
	for (int i = 0;i < particles.size();i++)
	{
		sf::FloatRect collRect = particles[i].rect.getGlobalBounds();

		for (int j =i+1;j < particles.size();j++)
		{
			
			if (particles[j].rect.getGlobalBounds().intersects((collRect)))
			{
				particles[j].changeColor();
			}
		}
	}
}

void ParticleSystem::spawnParticleExplosion(sf::Vector2f spawnPos,sf::Color c)
{
	sourcePosition = spawnPos;

	for (size_t i = 0; i < this->particles.size(); i++)
	{
		resetParticle(i,c);
	}
}

void ParticleSystem::draw(sf::RenderTarget & target)
{
	target.draw(vertices); 



	//for (auto &i : particles)
	//	target.draw(i.rect);

}

std::vector<sf::Vector2f> ParticleSystem::getRectPositions()
{
	std::vector<sf::Vector2f> buffer;
	buffer.reserve(particles.size());

	for (auto &i : particles)
		buffer.push_back(i.rect.getPosition());

	return buffer;
}

std::vector<sf::Vector2f> ParticleSystem::getVertexPositions()
{
	//std::vector<sf::Vector2f> buffer(vertices.getVertexCount());
	std::vector<sf::Vector2f> buffer;
	buffer.reserve(vertices.getVertexCount());
	for (size_t k = 0; k < this->vertices.getVertexCount(); k++)
	{
		sf::Vertex &p2 = vertices[k];
		buffer.push_back(p2.position);
	}

	return buffer;
}

sf::VertexArray & ParticleSystem::getVertex()
{
	return this->vertices;
}



/*


10particle

 0 -> 1 2 3 4 5 6 7 8 9 
 1 -> 2 3 4 5 6 7 8 9
 2 - > 3 4 5 6 7 8 9 



*/



int ParticleSystem::particlesWithGreen = 0;