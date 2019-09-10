#ifndef BUTTON_H
#define BUTTON_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

//IDLE IST NOTHING HAPPEN
enum button_states {BTN_IDLE,BTN_HOVER, BTN_ACTIVE};

class Button
{

	short unsigned buttonState;
	sf::RectangleShape shape;
	sf::Font *font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height, sf::Font *font, std::string text, short CharSize,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	const bool isPressed() const;
 	void update(const sf::Vector2f mousepos,Button **ptrHoveredButton);
	void render(sf::RenderTarget* target);

};

#endif
