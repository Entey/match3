#include "MenuChoiceLvl.h"

MenuChoiceLvl::MenuChoiceLvl(sf::RenderWindow & w, const sf::Texture & _logo, const sf::Texture & _back) : Base_Menu(w,_logo,_back)
{
	
	butTexture.loadFromFile("images/button_chose_level.png");
	texture.loadFromFile("images/lvl_background.png");
	sprite.setTexture(texture);
	sprite.setPosition(80, 180);

	texture_bon1.loadFromFile("images/knopka.png");
	texture_bon1.setSmooth(true);
	sprite_bon1.setTexture(texture_bon1);
	sprite_bon1.setScale(0.6, 0.6);
	sprite_bon1.setTextureRect(sf::IntRect(0, 0, 100, 100));
	sprite_bon1.setPosition(50, 350);

	texture_bon2.loadFromFile("images/molot.png");
	sprite_bon2.setTexture(texture_bon2);
	sprite_bon2.setScale(0.2, 0.2);
	sprite_bon2.setTextureRect(sf::IntRect(0, 0, 170, 300));
	sprite_bon2.setPosition(60, 420);

	Back.reset(new Button(_back, "Back", 600, 450, 20));
	Levels.reset(new vector<Button*>);
	info_levels.reset(new vector<Text_Line*>);
	scores.reset(new Text_Line());
	name.reset(new Text_Line());
	info_bonus1.reset(new Text_Line());
	info_bonus2.reset(new Text_Line());

	for(int i = 0; i < 5; i++)
		info_levels->push_back(new Text_Line());
	for (auto &a : *info_levels)
		a->setColor(255, 255, 255); // set color for text

	(*info_levels->at(0))(90, 200, "Level 1 :\n At this level you have to score 2000 points\n -- all bonuses are off\n -- you have 30 moves", 20);
	(*info_levels->at(1))(90, 200, "Level 2 :\n At this level you have to score 3000 points\n -- color bonus is off\n -- you have 3 minutes!", 20);
	(*info_levels->at(2))(90, 200, "Level 3 :\n At this level you have to score 2000 points\n -- color bonus is off\n -- you have 50 hummers\n -- you have no moves", 20);
	(*info_levels->at(3))(90, 200, "Level 4 :\n At this level you have to score 5000 points\n -- all bonuses are on\n -- you have 100 moves", 20);
	(*info_levels->at(4))(90, 200, "Level 5 :\n At this level you have to score 5000 points\n -- all bonuses are on\n -- you have 3 minutes!", 20);
	
}

int MenuChoiceLvl::execute()
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
					if (Back->getFocus()) { menu_type = 2; file.delete_temporary_data(); isMenu = false; }

					
					for (auto a : (*Levels)) {
						if (a->getFocus()) {
							menu_type = 4;
							return atoi(a->getName().c_str());
						}				
					}
				}
			}
		}
		
		window.clear();
		window.setView(view);
		window.draw(beckground);
		window.draw(sprite_bon1);
		window.draw(sprite_bon2);
		info_bonus1->Draw(window,0);
		info_bonus2->Draw(window,0);
		Back->Draw(window);
		scores->Draw(window, 0);
		name->Draw(window, 0);
		for (int i = 0; i < 5; i++) {
			Levels->at(i)->Draw(window);
				if (Levels->at(i)->getFocus()) {
					window.draw(sprite);
					info_levels->at(i)->Draw(window, 0);
				}
		}
		window.display();
	}
}

inline void MenuChoiceLvl::check_buttons()
{
	float a = 100, b = 100;	
	vec.clear();
	vec = file.load_player();
	name_player = file.read_temporary_data();
	for (int i = 1; i < 6; i++) {
		Levels->push_back(new Button(butTexture, i, a, b)); // create 5 buttons for 
		Levels->at(i - 1)->setActive(vec[i - 1]);
		
		a += 100;
	}
	(*scores)(50, 300, "Total Scores : " + std::to_string(vec[5]), 30); // upload player's scores 
	scores->setColor(50, 0, 0);
	(*name)(50, 10, name_player, 35); // upload player's names
	name->setColor(100, 20, 20);
	(*info_bonus1)(120,370, "removes all elements with set color", 20);
	(*info_bonus2)(120, 440, "removes a selected item", 20);

	for (auto &a : *Levels)
		a->setColor(110, 200, 200);
	
}
