#pragma once
#include <SFML/Graphics.hpp>
class ParticleSystem 
{


	static int particlesWithGreen;
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::RectangleShape rect;
		bool bColor=0;

		void changeColor() {
			bColor = !bColor;
			rect.setFillColor(bColor ?
				sf::Color::Green : sf::Color::Red);
		}


	};

	//m für membervaiarbles
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	sf::Time lifetime;
	sf::Vector2f sourcePosition;

public:
	ParticleSystem(unsigned int count);
	~ParticleSystem();

	void resetParticle(unsigned int i,sf::Color c);
	void setSourcePosition(sf::Vector2f sourcepos);
	void update(sf::Time elapsed);
	void checkCollideVertices();
	void checkCollideParticles();
	void spawnParticleExplosion(sf::Vector2f spawnPos, sf::Color c);

	void draw(sf::RenderTarget &target);

	std::vector<sf::Vector2f> getRectPositions();
	std::vector<sf::Vector2f> getVertexPositions();
	sf::VertexArray *getVertexPtr();
	sf::VertexArray &getVertex();

};

