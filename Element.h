#ifndef ELEMENT_H
#define ELEMENT_H

#include "SFML\Graphics.hpp"
#include <random>  
#include <ctime>
#include <iostream>
using namespace std;

static const sf::Image choice_image(int);

struct Element{
	sf::Texture texture;
	sf::Sprite sprite;
	int choice;
	
	Element() = delete;
	Element &operator=(const Element&) = delete;
	Element(const Element&) = delete;
	Element(const sf::Vector2f &coord);
};

#endif ELEMENT_H