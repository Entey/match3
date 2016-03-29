#ifndef GREED_ELEMENT_H
#define GREED_ELEMENT_H

#include "Element.h"
#include <iostream>
#include <memory>

class node {
	bool isEmpty, isSelected, isPut_in, isMove_inside, DellAnimation;
	sf::Vector2f coordinate;
	sf::Image image_blow;
	sf::Texture texture_blow;
	sf::Sprite sprite_blow;
	shared_ptr<Element> element;
public:
	node() : isEmpty(true), coordinate(0, 0), isSelected(false),  isMove_inside(true), isPut_in(false),
		DellAnimation(false) {}

	node(const sf::Vector2f &v) : isEmpty(true), isSelected(false), coordinate(v), isMove_inside(true), isPut_in(false),
			DellAnimation(false) {}

	void Blow_Animation()
		{
			image_blow.loadFromFile("images/blow.png");
			texture_blow.loadFromImage(image_blow);
			sprite_blow.setTexture(texture_blow);
			sprite_blow.setTextureRect(sf::IntRect(0,0,60,60));
			sprite_blow.setOrigin(30,30);
			sprite_blow.setPosition(coordinate);
			
		}

	void Create_element()
	{
		element.reset( new Element(coordinate));
	}

	void Del_element() {
		
		element.~shared_ptr();
	}

	sf::Sprite draww()
	{
		return element->sprite;
	}
	friend class Player;
};

#endif GREED_ELEMENT_H