#ifndef  BUTTON_H
#define BUTTON_H
#include <SFML\Graphics.hpp>
#include <memory>

class Button {
	bool is_choose { false };
	sf::Text text;
	sf::Sprite sprite;
	sf::Font f;
	sf::RectangleShape button_area;
	std::tr1::shared_ptr<sf::IntRect> Area;
	std::string name;
	bool is_draw{ true }, is_active{ true };
	unsigned int R{ 100 }, G{ 100 }, B{ 200 }; // color
public:
	Button(const sf::Texture &im, const sf::String &s, float x, float y, int size);
	Button(const sf::Texture &im, int i, float x, float y);
	void Draw(sf::RenderWindow &window);
	bool getFocus() { return is_choose; }
	std::string getName();
	void setColor(unsigned int R, unsigned int G, unsigned int B);
	bool is_Draw() { return is_draw; }
	void setDraw(bool b) { is_draw = b; }
	void setActive(bool b) { is_active = b; }
	sf::IntRect getArea() { return *Area; }
};

#endif // ! BUTTON_H