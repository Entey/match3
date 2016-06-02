#include "Button.h"
#include <iostream>
Button::Button(const sf::Texture &tx, const sf::String &s, float x, float y, int size) {
	name = s;
	f.loadFromFile("font.TTF");
	text.setCharacterSize(size);
	text.setFont(f);
	text.setString(s);
	text.setPosition(x+text.getCharacterSize()/8, y);
	sprite.setTexture(tx);
	sprite.setTextureRect(sf::IntRect(0,0,text.getGlobalBounds().width+ text.getCharacterSize()/3, text.getGlobalBounds().height + text.getCharacterSize()/3));
	sprite.setPosition(x, y);
	button_area.setFillColor(sf::Color(40, 40, 40));
	button_area.setSize(sf::Vector2f(sprite.getGlobalBounds().width + text.getCharacterSize() / 3, sprite.getGlobalBounds().height + text.getCharacterSize() / 3));
	button_area.setOrigin(button_area.getGlobalBounds().width / 2, button_area.getGlobalBounds().height / 2);
	button_area.setPosition(x+sprite.getGlobalBounds().width / 2, y+sprite.getGlobalBounds().height / 2);
	button_area.setOutlineThickness(2);
	button_area.setOutlineColor(sf::Color::Black);
	Area.reset( new sf::IntRect(x,y, button_area.getGlobalBounds().width, button_area.getGlobalBounds().height));
}

Button::Button(const sf::Texture & tx, int i, float x, float y)
{
	is_active = false;
	is_draw = false;
	name = std::to_string(i);
	
	f.loadFromFile("font.TTF");
	text.setCharacterSize(40);
	text.setFont(f);
	text.setString(name);
	sprite.setTexture(tx);
	sprite.setPosition(x, y);
	text.setPosition(x + sprite.getGlobalBounds().width/3, y + sprite.getGlobalBounds().height / 15);
	
	Area.reset(new sf::IntRect(x, y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
}

void Button::Draw(sf::RenderWindow & window)
{
	// intersection buttons with cursor
	if (is_active) {// if button is active
		if (Area->contains(sf::Mouse::getPosition(window))) {
			sprite.setColor(sf::Color(R - 50, G - 50, B - 50));
			text.setColor(sf::Color(R - 50, G - 50, B - 50));
			is_choose = true;
		}
		else {
			sprite.setColor(sf::Color(R, G, B));
			text.setColor(sf::Color(R, G, B));
			is_choose = false;
		}
	}
	else {
		sprite.setColor(sf::Color(90, 90, 90));
		text.setColor(sf::Color(90, 90, 90));
	}

	window.draw(button_area);
	window.draw(sprite);
	window.draw(text);
}


std::string Button::getName()
{
	return name;
}

void Button::setColor(unsigned int r = 255, unsigned int g = 255, unsigned int b = 255) {
	R = r; G = g; B = b;
}
