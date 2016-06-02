#include "Text_Line.h"

Text_Line::Text_Line()
{
	font.loadFromFile("Capture_it.ttf");
	text.setFont(font);
	text.setColor(sf::Color(50, 50, 50));
}

void Text_Line::setColor(unsigned int R, unsigned int G, unsigned int B)
{
	text.setColor(sf::Color(R,G,B));
}

void Text_Line::Draw(sf::RenderWindow & window, const float &time)
{
	if(time == 0) 
		window.draw(text);
	else
	{
		if (t < 10 && draw) {
			t += time*0.005;
			text.move(0, -time*0.05);
			window.draw(text);
		}
		else if (t >= 10) {
			t = 0.0;
			draw = false;
		}
	}
}

void Text_Line::setFount(std::string str)
{
	font.loadFromFile(str);
	text.setFont(font);
}

bool Text_Line::is_work()
{
	return draw;
}
