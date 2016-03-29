#ifndef MENU
#define MENU
#include <SFML\Graphics.hpp>

class Mmenu {
public:
	sf::Image image;
	sf::Texture texture, menuTexture1, menuTexture2, menuTexture3;
	sf::Sprite menu1, menu2, menu3;
	sf::Sprite sprite;
	sf::Vector2f coord;
	sf::RenderWindow &window;
	sf::RectangleShape back;
	sf::Event event;
	sf::View view;
	float ReturnTime;
	int menuNum;
	bool isMenu{ 1 };
public:
	Mmenu(sf::RenderWindow &w) :window(w) {
		menuTexture1.loadFromFile("images/111.png");
		menuTexture2.loadFromFile("images/222.png");
		menuTexture3.loadFromFile("images/333.png");
		menu1.setTexture(menuTexture1); menu2.setTexture(menuTexture2); menu3.setTexture(menuTexture3);

		back.setFillColor(sf::Color(0, 0, 0, 200));
		back.setSize(sf::Vector2f(window.getView().getSize().x, window.getView().getSize().y));

		image.loadFromFile("images/mmm.png");
		texture.loadFromImage(image);

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 700, 500));
		sprite.setPosition(sf::Vector2f(0, 0));

		menu1.setPosition(100, 30);
		menu2.setPosition(100, 90);
		menu3.setPosition(100, 150);

		view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));


	}
	float update(float time){

		ReturnTime = time;
		float frame = time*0.1;
		isMenu = true;
		while (isMenu) {
			menu1.setColor(sf::Color::White);
			menu2.setColor(sf::Color::White);
			menu3.setColor(sf::Color::White);
			menuNum = 0;

			if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
			if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }
			if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) { menu3.setColor(sf::Color::Blue); menuNum = 3; }
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (menuNum == 1)  { isMenu = false; } //если нажали первую кнопку, то выходим из меню 
				if (menuNum == 2) {}
				if (menuNum == 3)  { window.close(); return ReturnTime; }
			}


			while (window.pollEvent(event)){

				if (event.type == sf::Event::Closed){
					window.close();
					return ReturnTime;
				}
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q){
					return ReturnTime;
				}

			}

			window.clear();
			window.setView(view);
			window.draw(sprite);
			window.draw(menu1);
			window.draw(menu2);
			window.draw(menu3);
			window.display();
		}
		if (menuNum == 1) return 0;
	}
};

#endif MENU