#ifndef MAIN_GAME_H
#define MAIN_GAME_H
#include <iostream>
#include <string>
#include "Game_Algorithm.h"
#include "Menu.h"
#include "Game Interface.h"
#include "Menu\BaseM.h"
#include "Menu\MenuWelcome.h"
#include "Menu\MenuNewPlayer.h"
#include "Menu\MenuLoadPlayer.h"
#include "Menu\MenuChoiceLvl.h"
#include "Menu\Pause.h"

class Main_Game {
	std::string filename;
	sf::Image EndImage1; 
	sf::Texture EndTexture1; 
	sf::Texture EndTexture2; 
	sf::Image icon;

	sf::Sprite EndSprite1; 
	sf::Sprite EndSprite2; 
	
	sf::Image map_image; 
	sf::Texture map_texture; 
	sf::Image hum_image; 
	sf::Texture hum_texture; 
	sf::Image col_image; 
	sf::Texture col_texture; 
	sf::Image col_image1; 
	sf::Texture col_texture1; 
	sf::Image down_image; 
	sf::Texture down_texture; 
	sf::Image right_image; 
	sf::Texture right_texture; 

	sf::Texture logo; 
	sf::Image backgrIm; 
	sf::Texture beckgr; 
	sf::Image backgrImm; 
	sf::Texture beckgro; 
	sf::Font font;
	
	sf::Texture back_pause;
	sf::RenderWindow window; 
	sf::Event event;
	sf::Clock clock;

	int lvl = 0;
	std::vector<int> pl_info;

	bool algoLoop;
	std::tr1::shared_ptr<Game_Algorithm> p;
	std::tr1::shared_ptr<Game_Interface> interfac; 
	float _time;
	std::vector<Base_Menu*> vector_menu;
	std::shared_ptr<Pause> pause;
	FileWork file;
	sf::Text won_lost_text;
public:
	Main_Game();
	void menu_execute(int i = 0);
	void main_loop();
	~Main_Game();
};


#endif // !GAME_H