#include "Animation.h"


//updatet nur sprite und drawt nicht
//und bewet sprite auch nicht, updatet nur bilder abfolge


Animation::Animation()
{
}


Animation::~Animation()
{
}

Animation::Animation(const sf::Texture &tex,
	int x, int y, int w, int h, int imagecount, int rows)
{
	this->rows = rows;
	Frames = imagecount;
	frameheight = h;
	framewidth = w;
	sprite.setTexture(tex);


	sprite.setTextureRect(sf::IntRect(x, y, w, h));
	sprite.setOrigin(w / static_cast<float>(2), h / static_cast<float>(2));

	currentframe = 0;
	currentrow = 0;
	frametime = 0.4f;
	
}



void Animation::init(const sf::Texture &tex,
	int x, int y, int w, int h, int imagecount, int rows)
{
	this->rows = rows;
	Frames = imagecount;
	frameheight = h;
	framewidth = w;
	sprite.setTexture(tex);


	sprite.setTextureRect(sf::IntRect(x, y, w, h));
	sprite.setOrigin(w / static_cast<float>(2), h / static_cast<float>(2));

	currentframe = 0;
	currentrow = 0;
	frametime = 0.4f;

	sprite.setPosition(10, 10);

	sprite.setScale(sf::Vector2f(5, 5));

}



void Animation::setRotation(float rot)
{
	sprite.setRotation(rot);
}





void Animation::update(sf::Time _elapsed)
{
	elapsed += _elapsed;
	if (elapsed.asSeconds() > frametime)
	{
		currentframe++;
		if (currentframe >= Frames)currentframe = 0;
		elapsed = elapsed.Zero;
	}

	sprite.setTextureRect(sf::IntRect(currentframe*framewidth, currentrow * frameheight, framewidth, frameheight));

}

void Animation::draw(sf::RenderTarget & window)
{
	window.draw(sprite);



}

void Animation::setFrames(unsigned int frames)
{
	if (frames > 20)return;
	this->Frames = frames;
}

void Animation::setRows(unsigned int _rows)
{
	this->rows = _rows;
}

sf::Vector2f Animation::getPosition()
{
	return sprite.getPosition();
}

void Animation::setPosition(sf::Vector2f newPosition)
{
	sprite.setPosition(newPosition);
}

void Animation::move(sf::Vector2f velocity)
{
	sprite.move(velocity);

}



