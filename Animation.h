#pragma once
#include <SFML\Graphics.hpp>

//SIMPLE ANIMATION, ONE PICTURE CUT OUT FROM SPRITE
//USED FOR ITEMS

class Animation
{
	sf::Sprite sprite;
	sf::Time elapsed;


	float frametime;

	int framewidth, frameheight;
	int currentframe;
	int currentrow;
	int rows;
	int Frames;


public:

	Animation();
	explicit Animation(const sf::Texture &tex,
	int x, int y, int w, int h, int imagecount, int rows);
	~Animation();

	void init(const sf::Texture &tex,
		int x, int y, int w, int h, int imagecount, int rows);


	void setRotation(float rot);
	void update(sf::Time _elapsed);
	void setFrame(int Frame) { currentframe = Frame < Frames ? Frame : 0; };
	void setRow(int row) { this->currentrow = row < this->rows ? this->currentrow = row : 0; };
	void draw(sf::RenderTarget &window);
	void setFrames(unsigned int frames);
	void setRows(unsigned int _rows);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f newPosition);
	void move(sf::Vector2f velocity);

	const sf::Sprite &getSprite() { return this->sprite; }
	  	 
};



