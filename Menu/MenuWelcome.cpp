#include "MenuWelcome.h"


MenuWelcome::MenuWelcome(sf::RenderWindow & w, const sf::Texture & _logo, const sf::Texture & _back) : Base_Menu(w, _logo, _back)
{
	butTexture.loadFromFile("images/metal.png");
	ChoicePlayer.reset(new Button(butTexture, "Choice Player", 100, 300, 25)) ;
	NewPlayer.reset(new Button(butTexture, "New Player", 100, 350, 25));
	Quit.reset(new Button(butTexture, "Quit", 100, 400, 25));
	textline.reset(new Text_Line());
}

int MenuWelcome::execute()
{
	isMenu = true;
	while (isMenu) {
		_time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		_time = _time / 600;
		

		while (window.pollEvent(ev)) {
			if(sf::Event::MouseButtonPressed)
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (ChoicePlayer->getFocus()) { 
					if (file.num_of_names() <= 0) { menu_type = 2; isMenu = false; }
					else { menu_type = 2; isMenu = false; }
						
				}
				if (NewPlayer->getFocus()) { menu_type = 1; isMenu = false; }
				if (Quit->getFocus()) {
					window.close();	
					menu_type = 0;
					isMenu = false; 
					return (-1);
				}
			}
			
			if (ev.type == sf::Event::Closed)
				window.close();

		}

		window.clear();
			window.setView(view);
			window.draw(beckground);
			window.draw(logo);
			ChoicePlayer->Draw(window);
			NewPlayer->Draw(window);
			Quit->Draw(window);
			textline->Draw(window, _time);
		window.display();
	}
	return 0;
}
