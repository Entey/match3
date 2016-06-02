#include "Pause.h"

Pause::Pause(sf::RenderWindow & w, const sf::Texture & _logo, const sf::Texture & _back) : Base_Menu(w,_logo,_back)
{
	butTexture.loadFromFile("images/metal.png");
	Return.reset(new Button(butTexture, "Return", 270, 230, 30));
	Exit.reset(new Button(butTexture, "Exit", 300, 320, 30));
	back.reset(new sf::RectangleShape); 
	back->setFillColor(sf::Color(0, 0, 5, 4));
	back->setSize(sf::Vector2f(window.getView().getSize().x, window.getView().getSize().y));
}

float Pause::pause(float time)
{
	isMenu = true;
	while (isMenu) {
	
		while (window.pollEvent(ev)) {
			if(ev.type == sf::Event::MouseButtonPressed)
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (Return->getFocus()) {
						isMenu = false;
						return time;
					}
					if (Exit->getFocus()) return 0;
				}
			if(ev.type == sf::Event::KeyPressed)
				if(ev.key.code == sf::Keyboard::Pause || ev.key.code == sf::Keyboard::P || ev.key.code == sf::Keyboard::Escape) {
					isMenu = false;
					return time;
				}
		}

		window.setView(view);
		window.draw(*back);
		window.draw(beckground);
		Return->Draw(window);
		Exit->Draw(window);
		window.display();

	}
}
