#ifndef MENULOADPLAYER_H
#define MENULOADPLAYER_H
#include "BaseM.h"
//#include <map>

class Menu_Load_Player : public Base_Menu {
	std::tr1::shared_ptr<Button> Back;
	std::tr1::shared_ptr<Button> Dell;
	std::tr1::shared_ptr<vector<Button*>> Players;
	std::tr1::shared_ptr<Text_Line> dellTextLine;
	bool is_choose_dell{ false };
public:
	Menu_Load_Player(sf::RenderWindow &w, const sf::Texture &_logo, const sf::Texture & _back);
	int execute();
	inline void check_buttons();

};
#endif