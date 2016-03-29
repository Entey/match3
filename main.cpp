#include <iostream>

#include"Game_Algorithm.h"
#include "Menu.h"
#include <vector>
#include <sstream>
#include "map.h"


int main()
{
	sf::Image EndImage1; EndImage1.loadFromFile("images/mmm.png");
	sf::Texture EndTexture1; EndTexture1.loadFromImage(EndImage1);
	sf::Image EndImage2; EndImage2.loadFromFile("images/mmm.png");
	sf::Texture EndTexture2; EndTexture2.loadFromImage(EndImage2);

	sf::Sprite EndSprite1; EndSprite1.setTexture(EndTexture1);
	sf::Sprite EndSprite2; EndSprite2.setTexture(EndTexture2);
	EndSprite1.setTextureRect(sf::IntRect(0,0,1280,250));
	EndSprite2.setTextureRect(sf::IntRect(0,250,1280,250));


	sf::Image map_image; map_image.loadFromFile("images/map1.png");
	sf::Texture map_texture; map_texture.loadFromImage(map_image);
	sf::Sprite map_sprite; map_sprite.setTexture(map_texture);

	sf::Font font;
	font.loadFromFile("font.TTF");
	sf::Text text("",font,30);
	text.setColor(sf::Color(100,20,100));
	text.setPosition(510,100);



	
	
	sf::RenderWindow window(sf::VideoMode(700, 500), "Match3");
	sf::Event event;

Restart:
	sf::Clock clock;

	std::tr1::shared_ptr<Player> p(new Player);
	Mmenu menn(window);
	
	
	EndSprite1.setPosition(0,-250);
	EndSprite2.setPosition(0,500);
	float _time;
	
	_time = menn.update(0);
	
	while (window.isOpen())
	{
		
		_time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		_time = _time / 600;
		
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			

			if(event.type == sf::Event::KeyPressed)
				if(event.key.code == sf::Keyboard::Q) {
					_time = menn.update(_time);
					if(!_time) goto Restart;
					clock.restart();
				}

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Button::Right) {
					cout << "sdasd" << endl;
				}

			p->ClicMouse(event, window);
		}
		
		p->DropDown(_time);
		p->Swap(_time);
		p->Check_line();
		p->check_startline();

		std::ostringstream str1, str2;
		str1 << p->getSwapCount(); str2 << p->getScore();
		text.setString("Moves: " + str1.str() + "\nScore: " + str2.str());
		
		window.clear(sf::Color(150, 150, 150));

		for(int i=0; i<HEIGHT_MAP; i++)
		for(int j=0; j<WIDTH_MAP; j++)
		{
			if(TileMap[i][j] == '0') map_sprite.setTextureRect(sf::IntRect(0,0,167,167));
			if(TileMap[i][j] == ' ') map_sprite.setTextureRect(sf::IntRect(0,338,167,167));
			map_sprite.setPosition(j*167,i*167);
			window.draw(map_sprite);
		}


		if (p->GetSwapCount() <= 0) {
			EndSprite1.move(0,_time*0.1);			
			EndSprite2.move(0,_time*-0.1);
			if(EndSprite1.getPosition().y >= 0){
			_time = menn.update(_time);
			if(!_time) goto Restart;
			clock.restart();}
		}


		p->show(window);
		window.draw(text);
		p->Graphics(_time, window);
		p->TimeLine(_time, window, 2);
		
		window.draw(EndSprite1);
		window.draw(EndSprite2);
		
		window.display();
		
	}
	return 0;
}
