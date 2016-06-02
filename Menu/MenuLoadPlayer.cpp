#include "MenuLoadPlayer.h"
#include <iostream>

Menu_Load_Player::Menu_Load_Player(sf::RenderWindow & w, const sf::Texture & _logo, const sf::Texture & _back) : Base_Menu(w, _logo, _back)
{
	butTexture.loadFromFile("images/metal.png");
	Back.reset(new Button(butTexture, "Back", 510, 450, 20));
	Dell.reset(new Button(butTexture, "Dell", 500, 300, 30));
	Dell->setColor(30, 30, 30);

	dellTextLine.reset(new Text_Line()); (*dellTextLine)(450, 350, "For delete any player activate \n/""DELL/""- button, and click to name player", 10);
	Players.reset(new vector<Button*>);
	
	
}

int Menu_Load_Player::execute()
{
	check_buttons();
	isMenu = true;
	while (isMenu) {
		_time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		_time = _time / 600;
		
		
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed)
				window.close();
			
			if (ev.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (Back->getFocus()) { menu_type = 0; Dell->setColor(20, 20, 20); is_choose_dell = false; return 0; }

					if (Dell->getFocus()) {
						if (!is_choose_dell) {
							Dell->setColor(255, 100, 100);
							is_choose_dell = true;
						}
						else {
							Dell->setColor(20, 20, 20);
							is_choose_dell = false;
							}
						}

					for (auto a : (*Players)) {
						if (a->getFocus() && is_choose_dell && a->is_Draw()) {
							a->setDraw(false);
							file.delete_player(a->getName());
							continue;
						}
						else if (a->getFocus() && a->is_Draw()) {
							file.create_temporary_data(a->getName());
							menu_type = 3; isMenu = false;
						}
					}
				}
			 }
		}
		
		window.clear();
		window.setView(view);
		window.draw(beckground);
		window.draw(logo);
		Back->Draw(window);
		Dell->Draw(window);
		
		int i = 0;
		while (i < Players->size()) {
			if(Players->at(i)->is_Draw())
			Players->at(i)->Draw(window);
			i++;
		}
		dellTextLine->Draw(window, 0);
		window.display();
	}
	return 0;
}

void Menu_Load_Player::check_buttons()
{
	float a = 50, b = 300;
	vector<string> vec = file.load_players_names();
	int num = file.num_of_names();

	if (!Players->empty()) {
		for (auto &a : (*Players))
			delete a;
		Players->clear();
	}
	
	for (int i = 0; i < num; i++) {
		if (i == 3) { b = 300; a = 300; }
		Players->push_back(new Button(butTexture, vec.at(i), a, b, 25));
		b += 50;
	}
	
	for (auto & a : (*Players)) 
		a->setColor(90, 120, 120);
}
