#include "BaseM.h"

Base_Menu::Base_Menu(sf::RenderWindow & w, const sf::Texture & _logo, const sf::Texture & _back): window(w) {
	logo.setTexture(_logo);
	logo.setScale(0.4, 0.4);
	logo.setPosition(150, 10);
	beckground.setTexture(_back);
	beckground.setPosition(0, 0);

	view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
}
