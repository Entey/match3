#ifndef GAME_ALGORITHM_H
#define GAME_ALGORITHM_H


#include "Greed_Element.h"
#include "Game Interface.h"
#include <fstream>


const int n = 8;
using namespace sf;


class Game_Algorithm {
	node grid[n][n];   // сітка елементів
	node *p[n*n];      // потрібно для видалення елементів
	float  angle, frame;
	vector<sf::Vector2f> coord;
	float x, y, swap_count, score, isPosibleSwap;
	bool isMove, isSelectedHum{ false }, isPushedColBon{ false }, bWhich_col{false};
	sf::Vector2i pixelPos; // для захвату курсора
	sf::Vector2f pos;  // для визначення позиції курсору
	vector<node*> vec_for_dell;
	vector<node*>::iterator it_dell;
	int  hum_bonus{ 0 }, color_bonus{ 0 }, which_col;  // more then three
	sf::Texture cursor_texture;
	sf::Sprite area_hum, area_col, cursor;
	bool horizontal{ false }, vertical{ false };
	float lvl_time{ 0.0 };

public:
	Game_Algorithm();
	void Generation_grid();
	void Swap(node& left, node &right);
	void Swap_Elements(const float &time);
	void Check_Startline();
	void DropDown(const float &time);
	void Graphics_Blow(float time, sf::RenderWindow & window);
	void ClicMouse(const sf::Event &ev, sf::RenderWindow &window);
	void Check_line();  // перевірка ліній на видалення 3 та більше елементів
	void Show(sf::RenderWindow &window);
	void update(float time);
	void set_lvl(int num);
	void setAreaHum(const sf::Sprite &s) { area_hum = s; }
	void setAreaCol(const sf::Sprite &c) { area_col = c; }
	void setColorBonus();
	
	float getTimelvl();
	int getSwapCount();
	int getScore(); 
	int getHumBunus();
	int getColBonus();
	int get_Color();
	bool getIsMove();
	int Successlvl(int i);
};


#endif GAME_ALGORITHM_H