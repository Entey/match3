#include <iostream>
#include"Game_Algorithm.h"
#include "Menu.h"
#include <vector>
#include "D:\Projects\Match3\Match3\Match3\Game Interface.h"





int main()
{
	sf::Image EndImage1; EndImage1.loadFromFile("images/mmm.png");
	sf::Texture EndTexture1; EndTexture1.loadFromImage(EndImage1);
	sf::Texture EndTexture2; EndTexture2.loadFromImage(EndImage1);

	sf::Sprite EndSprite1; EndSprite1.setTexture(EndTexture1);
	sf::Sprite EndSprite2; EndSprite2.setTexture(EndTexture2);
	EndSprite1.setTextureRect(sf::IntRect(0,0,1280,250));
	EndSprite2.setTextureRect(sf::IntRect(0,250,1280,250));


	sf::Image map_image; map_image.loadFromFile("images/back.png");
	sf::Texture map_texture; map_texture.loadFromImage(map_image);
	sf::Image hum_image; hum_image.loadFromFile("images/molot.png");
	sf::Texture hum_texture; hum_texture.loadFromImage(hum_image);
	sf::Image col_image; col_image.loadFromFile("images/knopka.png");
	sf::Texture col_texture; col_texture.loadFromImage(col_image);
	sf::Image col_image1; col_image1.loadFromFile("images/but1.png");
	sf::Texture col_texture1; col_texture1.loadFromImage(col_image1);
	sf::Image down_image; down_image.loadFromFile("images/down.png");
	sf::Texture down_texture; down_texture.loadFromImage(down_image);
	sf::Image right_image; right_image.loadFromFile("images/right.png");
	sf::Texture right_texture; right_texture.loadFromImage(right_image);

	

	sf::Font font;
	font.loadFromFile("font.TTF");
		
	sf::RenderWindow window(sf::VideoMode(700, 500), "Match3");
	sf::Event event;

Restart:
	sf::Clock clock;

	std::tr1::shared_ptr<Player> p(new Player);
	Mmenu menn(window);
	Game_Interface interfac(map_texture, hum_texture, col_texture, col_texture1, down_texture, right_texture, font);
	
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
			p->ClicMouse(event, window);
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
				if(event.key.code == sf::Keyboard::Q) {
					_time = menn.update(_time);
					if(!_time) goto Restart;
					clock.restart();
				}			
		}
		
		p->setAreaHum(interfac.GetHummerSp());
		p->setAreaCol(interfac.GetColorSp());
		p->DropDown(_time);
		p->Swap_Elements(_time);
		p->Check_line();
		p->setColorBonus();
		p->Check_Startline();
		
		
		interfac.Set_Text(p->getSwapCount(), p->getScore(), p->getHumBunus(), p->getColBonus());
		interfac.Set_Buttons(p->getHumBunus(), p->getColBonus(), p->get_Color());
		interfac.TimeLine(_time, p->getSwapCount(), 1);


		if (p->getSwapCount() <= 0 && !p->getIsMove()) {
			EndSprite1.move(0, _time*0.1);
			EndSprite2.move(0, _time*-0.1);
			if (EndSprite1.getPosition().y >= 0) {
				_time = menn.update(_time);
				if (!_time) goto Restart;
				clock.restart();
			}
		}

		window.clear(sf::Color(150, 150, 150));
		interfac.Draw(window);
		p->Show(window);
		p->Graphics_Blow(_time, window);
		window.draw(EndSprite1);
		window.draw(EndSprite2);
		window.display();
		
	}
	return 0;
}
