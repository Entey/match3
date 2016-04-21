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
	std::tr1::shared_ptr<Element> element;
public:
	node();

	node(const sf::Vector2f &v);

	void Blow_Animation();

	void Create_element() { element.reset(new Element(coordinate)); }
	void Del_element() { element.~shared_ptr(); }
	sf::Sprite draww() { return element->sprite; }
	friend class Player;
};

#endif GREED_ELEMENT_H