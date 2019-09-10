#include "Button.h"




Button::Button(float x, float y, float width, float height, sf::Font * font, std::string text, short CharSize,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{



	this->buttonState = BTN_IDLE;

	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Blue);
	this->text.setCharacterSize(CharSize);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width/2.f)- this->text.getGlobalBounds().width /2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)- this->text.getGlobalBounds().height /2
	);

}

Button::~Button()
{
}



const bool Button::isPressed() const
{
	if(this->buttonState ==  BTN_ACTIVE)
	return true;

	return false;
}

void Button::update(const sf::Vector2f mousepos, Button **ptrHoveredButton)
{
	
	this->buttonState = BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousepos))
	{
		this->buttonState = BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
			
		}
		else {
			*ptrHoveredButton = this;
			printf("button hovered\n");
		}

	}

	switch (this->buttonState)
	{
	case BTN_IDLE: this->shape.setFillColor(this->idleColor);
		text.setFillColor(sf::Color::Blue);
		break;
	case BTN_HOVER: this->shape.setFillColor(this->hoverColor);
		text.setFillColor(sf::Color::White);
		break;
	case BTN_ACTIVE: this->shape.setFillColor(this->hoverColor);
		break;
	default:this->shape.setFillColor(sf::Color::Red);
		break;
	}

}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape);
	target->draw(this->text);

}
