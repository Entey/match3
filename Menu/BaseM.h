#ifndef BASEM_H
#define BASEM_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "..\Button.h"
#include "..\Input_Line.h"
#include "..\Text_Line.h"
#include "..\FileWork.h"
using namespace std;

class Base_Menu {

protected:
	sf::Sprite beckground;
	sf::Sprite logo;
	sf::RenderWindow &window;
	sf::Event ev;
	sf::View view;
	sf::Clock clock;
	FileWork file;
	sf::Texture butTexture;
	float _time;
	bool isMenu{ 1 };
	int menu_type{ 0 };
	string name_player;
public:
	Base_Menu(sf::RenderWindow &w, const sf::Texture &_logo, const sf::Texture & _back);
	virtual int execute() = 0;
	int	communication() { return menu_type; }

};


#endif // !BASEM_H