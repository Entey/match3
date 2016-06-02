#include "MenuNewPlayer.h"

MenuNewPlayer::MenuNewPlayer(sf::RenderWindow & w, const sf::Texture & _logo, const sf::Texture & _back) : Base_Menu(w, _logo, _back)
{
	butTexture.loadFromFile("images/metal.png");
	Back.reset(new Button(butTexture, "Back", 600, 450, 20));
	Enter.reset(new Button(butTexture, "Enter", 230, 360, 30));
	Inpline.reset(new Input_Line(30, 100, 310));
	static_line.reset(new Text_Line()); (*static_line)(100, 270, "Input your name", 30);
	textline.reset(new Text_Line());
}

int MenuNewPlayer::execute()
{
	isMenu = true;
	while (isMenu) {
		_time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		_time = _time / 600;

		while (window.pollEvent(ev)) {

			if (ev.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (Back->getFocus()) { menu_type = 0; isMenu = false; }
					
					if (Enter->getFocus()) {
						if (file.num_of_names() >= 6) {
							(*textline)(Enter->getArea().left + Enter->getArea().width, Enter->getArea().top, "To many players", 20);
							menu_type = 2; isMenu = false;
						}
						else {
							(*textline)(Enter->getArea().left + Enter->getArea().width, Enter->getArea().top, file.create_new_player(Inpline->get_name_player()), 20);
							menu_type = 2; isMenu = false;
						}
					}
				}
			}
			Inpline->exec(window, ev);
			if (ev.type == sf::Event::Closed)
				window.close();

		}

		window.clear();
		window.setView(view);
		window.draw(beckground);
		window.draw(logo);
		Back->Draw(window);
		Enter->Draw(window);
		Inpline->show(window);
		textline->Draw(window, _time);
		static_line->Draw(window, 0);
		window.display();
	}
	return 0;
}
