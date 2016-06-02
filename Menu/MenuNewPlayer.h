#ifndef MENUNEWPLAYER_H
#define MENUNEWPLAYER_H
#include "BaseM.h"
#include "../Input_Line.h"

class MenuNewPlayer : public Base_Menu {
	std::tr1::shared_ptr<Button> Back;
	std::tr1::shared_ptr<Button> Enter;
	std::tr1::shared_ptr<Input_Line> Inpline;
	std::tr1::shared_ptr<Text_Line> textline;
	std::tr1::shared_ptr<Text_Line> static_line;
public:
	MenuNewPlayer(sf::RenderWindow &w, const sf::Texture &_logo, const sf::Texture & _back);
	int execute();

};


#endif // !MENUWELCOME_H