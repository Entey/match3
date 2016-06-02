#include "Main_Game.h"

Main_Game::Main_Game() {
	window.create(sf::VideoMode(700, 500),"Hexagons", sf::Style::Titlebar);
	icon.loadFromFile("images/icon.png");
		window.setIcon(32,32,icon.getPixelsPtr());

	EndImage1.loadFromFile("images/mmm.png");
	EndTexture2.loadFromImage(EndImage1);
	EndTexture1.loadFromImage(EndImage1);
	EndSprite1.setTexture(EndTexture1);
	EndSprite2.setTexture(EndTexture2);
	EndSprite1.setTextureRect(sf::IntRect(0, 0, 1280, 250));
	EndSprite2.setTextureRect(sf::IntRect(0, 250, 1280, 250));

	map_image.loadFromFile("images/back.png");
	map_texture.loadFromImage(map_image);
	hum_image.loadFromFile("images/molot.png");
	hum_texture.loadFromImage(hum_image);
	col_image.loadFromFile("images/knopka.png");
	col_texture.loadFromImage(col_image);
	col_image1.loadFromFile("images/but1.png");
	col_texture1.loadFromImage(col_image1);
	down_image.loadFromFile("images/down.png");
	down_texture.loadFromImage(down_image);
	right_image.loadFromFile("images/right.png");
	right_texture.loadFromImage(right_image);



	back_pause.loadFromFile("images/pause1.png");
	logo.loadFromFile("images/logo.png");
	backgrIm.loadFromFile("images/mmm.png");
	beckgr.loadFromImage(backgrIm);
	backgrImm.loadFromFile("images/mmmm.png");
	beckgro.loadFromImage(backgrImm);
	font.loadFromFile("font.TTF");

	

	
	interfac.reset(new Game_Interface(map_texture, hum_texture, col_texture, col_texture1, down_texture, right_texture, font));
	vector_menu.push_back(new MenuWelcome(window, logo, beckgr));
	vector_menu.push_back(new MenuNewPlayer(window, logo, beckgr));
	vector_menu.push_back(new Menu_Load_Player(window, logo, beckgr)); 
	vector_menu.push_back(new MenuChoiceLvl(window, logo, beckgro));
	pause.reset(new Pause(window, logo, back_pause));

	won_lost_text.setFont(font);
	won_lost_text.setCharacterSize(30);
	won_lost_text.setColor(sf::Color(0, 255, 0));
	won_lost_text.setPosition(270, 100);
}

void Main_Game::menu_execute(int i)
{	
	while (i <= 3) {
			lvl = vector_menu[i]->execute();
			if (lvl < 0) { return; } // for correct exit game
			i = vector_menu[i]->communication();
	}
	
	pl_info.clear();
	pl_info = file.load_player();
}

void Main_Game::main_loop()
{
	menu_execute(); // call menu before start game
	bool change;

	while (true) {  // loop our game
		if (lvl < 0) break; 
		EndSprite1.setPosition(0, -250);
		EndSprite2.setPosition(0, 500);
		algoLoop = true;
		change = true;
		p.reset(new Game_Algorithm()); // create new game algorithm
		
		p->set_lvl(lvl);
		won_lost_text.setString("YOU LOST!");
		while (algoLoop) // loop game algorithm
		{
		
			_time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			_time = _time / 600;

			while (window.pollEvent(event))
			{
				p->ClicMouse(event, window);
				
				if (event.type == sf::Event::LostFocus) {
					_time = pause->pause(_time);
					if (!_time) algoLoop = false;
					clock.restart();
				}

				if (event.type == sf::Event::KeyPressed)
					if (event.key.code == sf::Keyboard::Pause || event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Escape) {
						_time = pause->pause(_time);
						if (!_time) algoLoop = false;
						clock.restart();
					}
			}

			p->setAreaHum(interfac->GetHummerSp());
			p->setAreaCol(interfac->GetColorSp());
			p->update(_time);


			interfac->Set_Text(p->getSwapCount(), p->getScore(), p->getHumBunus(), p->getColBonus());
			interfac->Set_Buttons(p->getHumBunus(), p->getColBonus(), p->get_Color());
			interfac->TimeLine(p->getTimelvl(), p->getSwapCount());
			interfac->Set_Button(_time);
			
			window.clear();
			interfac->Draw(window);
			p->Show(window);
			p->Graphics_Blow(_time, window);

			int succ = p->Successlvl(lvl);
			if (succ == 1) {
				if (lvl < 5) {
					if ((pl_info[lvl] == 0) && change) {
						pl_info[lvl] = 1;												// give access to the next level
						pl_info[5] += p->getScore();									// add scores
						file.change_info_player(file.read_temporary_data(), pl_info);	// and make changes to the file
						change = false;													// stop algorithm loop
					}
				}
				won_lost_text.setString("YOU WON!");
				EndSprite1.move(0, _time*0.1);
				EndSprite2.move(0, _time*-0.1);
				window.draw(EndSprite1);
				window.draw(EndSprite2);
				window.draw(won_lost_text);
				if (EndSprite1.getPosition().y >= 0) {
					break;
				}
			}
			else if (succ == 2) {
				EndSprite1.move(0, _time*0.1);
				EndSprite2.move(0, _time*-0.1);
				window.draw(EndSprite1);
				window.draw(EndSprite2);
				window.draw(won_lost_text);
				if (EndSprite1.getPosition().y >= 0) {
					break;
				}
			}
			window.display();
		}
		
		menu_execute(3);  // call MenuChoiceLevel
		
	}
}

Main_Game::~Main_Game()
{
	for (auto &a : vector_menu)
		delete a;
}
