#ifndef MENU_H
#define MENU_H
#include <SFML\Graphics.hpp>
#include "Input_Line.h"

class Mmenu {
public:
	sf::Image image;
	sf::Texture texture, menuTexture1, menuTexture2, menuTexture3;
	sf::Sprite menu1, menu2, menu3;
	sf::Sprite sprite;
	sf::Vector2f coord;
	sf::RenderWindow &window;
	sf::RectangleShape back;
	sf::Event ev;
	sf::View view;
	float ReturnTime;
	int menuNum;
	bool isMenu{ 1 };
	Input_Line *inp;
public:
	Mmenu(sf::RenderWindow &w);
	float update(float time);
};

#endif MENU_H