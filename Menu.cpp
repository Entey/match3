#include "Menu.h"

Mmenu::Mmenu(sf::RenderWindow &w) :window(w) {
	menuTexture1.loadFromFile("images/button_chose_level.png");
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
	inp = new Input_Line(25, 250, 300);

}

float Mmenu::update(float time){

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
		

		while (window.pollEvent(ev)){
			
			inp->exec(window, ev);
			if (ev.type == sf::Event::Closed){
				window.close();
				return ReturnTime;
			}
			if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Q){
				return ReturnTime;
			}
			
		}

		window.clear();
		window.setView(view);
		window.draw(sprite);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		inp->show(window);
		window.display();
	}
	if (menuNum == 1) return 0;
}