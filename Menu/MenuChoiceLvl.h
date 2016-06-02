#ifndef MENUCHOICELVL_H
#define MENUCHOICELVL_H
#include "BaseM.h"

class MenuChoiceLvl : public Base_Menu {
	std::tr1::shared_ptr<Button> Back;
	std::tr1::shared_ptr<vector<Button*>> Levels;
	std::tr1::shared_ptr<vector<Text_Line*>> info_levels;
	std::tr1::shared_ptr<Text_Line> info_bonus1;
	std::tr1::shared_ptr<Text_Line> info_bonus2;
	std::tr1::shared_ptr<Text_Line> scores;
	std::tr1::shared_ptr<Text_Line> name;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape textur;
	sf::Texture texture_bon1;
	sf::Texture texture_bon2;
	sf::Sprite sprite_bon1;
	sf::Sprite sprite_bon2;
	vector<int> vec;
public:
	MenuChoiceLvl(sf::RenderWindow &w, const sf::Texture &_logo, const sf::Texture & _back);
	int execute();
	inline void check_buttons();

};


#endif // !MENUCHOICELVL_H