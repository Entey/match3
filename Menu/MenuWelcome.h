#ifndef MENUWELCOME_H
#define MENUWELCOME_H
#include "BaseM.h"

class MenuWelcome : public Base_Menu {
	std::tr1::shared_ptr<Button> ChoicePlayer;
	std::tr1::shared_ptr<Button> NewPlayer;
	std::tr1::shared_ptr<Button> Quit;
	std::tr1::shared_ptr<Text_Line> textline;
public:
	MenuWelcome(sf::RenderWindow &w, const sf::Texture &_logo, const sf::Texture & _back);
	int execute();

};


#endif // !MENUWELCOME_H