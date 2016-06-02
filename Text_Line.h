#ifndef TEXT_LINE_H
#define TEXT_LINE_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
class Text_Line {
	sf::Font font;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text text;
	float t{0};
	bool draw{ false };
public:
	Text_Line();
	void operator()(int x, int y, std::string str, unsigned int size) {
			text.setString(str.c_str());
			text.setPosition(x, y);
			text.setCharacterSize(size);
			draw = true;
	}

	void setColor(unsigned int R, unsigned int G, unsigned int B);

	void Draw(sf::RenderWindow &window, const float &time);
	void setFount(std::string);
	bool is_work();
};



#endif

