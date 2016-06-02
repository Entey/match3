#ifndef INPUT_LINE_H
#define INPUT_LINE_H
#include <iostream>
#include <sstream>
#include <cctype>
#include <SFML\Graphics.hpp>

class Input_Line {
	sf::RectangleShape area;
	sf::Text text;
	std::string str;
	sf::Font font;
	int max_characters{ 10 };
	sf::Vector2f size;
	bool bInput{ true }, bText{ true };
public:
	Input_Line(float _size, float _x, float _y);
	bool actvate();
	void exec(sf::RenderWindow &window, sf::Event &ev);
	std::string get_name_player() { return str; }
	void show(sf::RenderWindow &window);
};



#endif INPUT_LINE_H
