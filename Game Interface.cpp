#include "Game Interface.h"


Game_Interface::Game_Interface(sf::Texture &back, sf::Texture &hummer, sf::Texture &color, sf::Texture &color1, sf::Texture &down, sf::Texture &right, sf::Font &font) : level_time(100.0) {
	background.setTexture(back);
	background.setPosition(0, 0);

	Hummer.setTexture(hummer);
	Hummer.setPosition(550, 240);
	Hummer.setScale(0.2, 0.2);

	color.setSmooth(true);
	color1.setSmooth(true);
	down.setSmooth(true);

	Color.setTexture(color);
	Color.setPosition(575, 385);
	Color.setScale(0.6, 0.6);
	Color.setOrigin(50, 50);
	Color1.setTexture(color1);
	Color1.setPosition(575, 385);
	Color1.setScale(0.5, 0.5);
	Color1.setOrigin(75, 75);
	Color2.setTexture(color1);
	Color2.setOrigin(75, 75);
	Color2.setPosition(575, 385);
	Color2.setScale(0.5, 0.5);
	
	Right.setTexture(right);
	Right.setPosition(450, 0);
	
	Down.setTexture(down);
	Down.setPosition(5, 430);

	LineTime.reset(new sf::RectangleShape);
	LineTime->setSize(sf::Vector2f(level_time, 10));
	LineTime->setOrigin(level_time, 10);
	LineTime->setFillColor(sf::Color(10, 250, 150));
	
	text1.setCharacterSize(25);
	text1.setFont(font);
	text1.setString("");
	text1.setColor(sf::Color(100, 20, 100));
	text1.setPosition(500, 75);

	text2.setCharacterSize(30);
	text2.setFont(font);
	text2.setString("");
	text2.setColor(sf::Color(100, 150, 100));
	text2.setPosition(597, 270);
}

void Game_Interface::Draw(sf::RenderWindow & window){
	
	window.draw(background);
	window.draw(Right);
	window.draw(*LineTime);
	window.draw(Down);
	window.draw(Hummer);
	
	window.draw(Color2);
	window.draw(Color1);
		
	window.draw(Color);
	window.draw(text1);
	window.draw(text2);

}

void Game_Interface::Set_Buttons(int countHum, int countCol, int whitch_col){
	switch (countHum){
	case 0:
		Hummer.setTextureRect(sf::IntRect(0, 0, 170, 300));
		break;
	default:
		Hummer.setTextureRect(sf::IntRect(170, 0, 170, 300));
		break;
	}
	switch (countCol) {
	case 0: Color.setTextureRect(sf::IntRect(0, 0, 100, 100));
		isColor = false; Color.setColor(sf::Color::White); Color1.setColor(sf::Color::White); Color2.setColor(sf::Color::White); background.setColor(sf::Color::White);
		break; 
	case 1: Color.setTextureRect(sf::IntRect(100, 0, 100, 100));
		break;
	case 2: Color.setTextureRect(sf::IntRect(200, 0, 100, 100));
		break;
	default: Color.setTextureRect(sf::IntRect(300, 0, 100, 100));
		if (!isColor) {
			switch (whitch_col) {
			case 1:
				Color.setColor(sf::Color::Red); Color1.setColor(sf::Color::Red); Color2.setColor(sf::Color::Red);
				background.setColor(sf::Color::Red);
				break;
			case 2:
				Color.setColor(sf::Color::Green); Color1.setColor(sf::Color::Green); Color2.setColor(sf::Color::Green);
				background.setColor(sf::Color::Green);
				break;
			case 3:
				Color.setColor(sf::Color::Blue); Color1.setColor(sf::Color::Blue); Color2.setColor(sf::Color::Blue);
				background.setColor(sf::Color::Blue);
				break;
			case 4:
				Color.setColor(sf::Color::Yellow); Color1.setColor(sf::Color::Yellow); Color2.setColor(sf::Color::Yellow);
				background.setColor(sf::Color::Yellow);
				break;
			case 5:
				Color.setColor(sf::Color::Magenta); Color1.setColor(sf::Color::Magenta); Color2.setColor(sf::Color::Magenta);
				background.setColor(sf::Color::Magenta);
				break;
			}
			isColor = true;
		}
		break;
	}
}


void Game_Interface::TimeLine(float lvl_time, int swap_count){
	LineTime->setPosition(sf::Vector2f(420, 485));
	level_time = lvl_time;
	if (level_time > 0.0) {
		LineTime->setOrigin(level_time, 40);
		LineTime->setSize(sf::Vector2f(level_time, 40));
	}
	else{
		LineTime->setOrigin(swap_count, 40);
		LineTime->setSize(sf::Vector2f(swap_count, 40));
	}

	
}

void Game_Interface::Set_Text(int SwapCount,int Score, int Hum, int Col){
	std::ostringstream str1, str2, str3;
	str1 << SwapCount; str2 << Score; str3 << Hum;
	text1.setString("  Moves: " + str1.str() + "\n\nScores: " + str2.str());
	text2.setString(str3.str());
}

void Game_Interface::Set_Button(float time)
{
	if (isColor) {
		Color1.rotate(0.1*time);
		Color2.rotate(-0.1*time);
	}
	else {
		Color1.setRotation(0);
		Color2.setRotation(90);
	}
}

