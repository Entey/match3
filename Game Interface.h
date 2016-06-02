#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <SFML\Graphics.hpp>
#include <memory>
#include <sstream>
#include <iostream>
using namespace std;

class Game_Interface {
	sf::Sprite background;
	sf::Sprite Hummer;
	sf::Sprite Color, Color1, Color2;
	sf::Sprite Down;
	sf::Sprite Right;
	sf::Text text1;
	sf::Text text2;
	bool isColor{false};
	
	float level_time;
	std::tr1::shared_ptr<sf::RectangleShape> LineTime;
public:
	Game_Interface(sf::Texture &back, sf::Texture &hummer, sf::Texture &color, sf::Texture &color1, sf::Texture &down, sf::Texture &right, sf::Font &f);
	void Draw(sf::RenderWindow & window);
	void Set_Buttons(int countHum = 0, int countCol =0, int whitch_col = 1);
	void TimeLine(float time, int swap_count);
	void Set_Text(int SwapCount,int Score, int Hum=0, int Col=0);
	void Set_Button(float t);
	sf::Sprite GetHummerSp() { return Hummer; }
	sf::Sprite GetColorSp() { return Color; }
};




#endif GAME_INTERFACE_H