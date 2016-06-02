#ifndef PAUSE_H
#define PAUSE_H
#include "BaseM.h"

class Pause : public Base_Menu {
	std::tr1::shared_ptr<Button> Return;
	std::tr1::shared_ptr<Button> Exit;
	std::tr1::shared_ptr<sf::RectangleShape> back;
	float returnTime;
	bool isMenu{ true };
public:
	int execute() { return 0; }
	Pause(sf::RenderWindow &w, const sf::Texture &_logo, const sf::Texture & _back);
	float pause(float time);

};


#endif // !PAUSE_H