#include "Input_Line.h"


Input_Line::Input_Line(float _size, float _x, float _y)
{
	font.loadFromFile("font.TTF");
	text.setFont(font);
	text.setPosition(_x+_size/3, _y);
	text.setColor(sf::Color(100, 100, 100));
	text.setCharacterSize(_size);
	text.setString("");
	size.x = (_size-_size/4.5)*10; size.y = _size+5;
	area.setSize(size);
	area.setOutlineThickness(2.3);
	area.setOutlineColor(sf::Color(100, 100, 100));
	area.setFillColor(sf::Color::Black);
	area.setPosition(_x, _y);
}

bool Input_Line::actvate()
{
	if (max_characters == 10 || !bInput)
		return false;
	else 
		return true;
}

void Input_Line::show(sf::RenderWindow & window)
{
	window.draw(area);
	window.draw(text);
}

void Input_Line::exec(sf::RenderWindow &window, sf::Event &ev) {
				if (!actvate())
					area.setFillColor(sf::Color(20,20,20));
				else
					area.setFillColor(sf::Color(30,30,30));

		
				if (ev.type == sf::Event::KeyPressed) {
					if (ev.key.code == sf::Keyboard::Escape)  // finish entering name
						bInput = false;

					if (ev.key.code == sf::Keyboard::BackSpace && max_characters < 10 && bInput) { // erace character
						str.pop_back();	++max_characters;
						bText = false;
					}
					else
						bText = true;
				}
				
				if (ev.type == sf::Event::TextEntered && bText  && bInput && max_characters > 0) { // input name
						if (ev.text.unicode < 128) {
							char ch = static_cast<char>(ev.text.unicode);
							if (std::isalpha(ch)) {
								str.push_back(ch);
								--max_characters;
							}
						}
					}
				for (auto &a : str) a = toupper(a);
		text.setString(str);
	}



