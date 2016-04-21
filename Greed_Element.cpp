#include "Greed_Element.h"

node::node() : isEmpty(true), coordinate(0, 0), isSelected(false), isMove_inside(true), isPut_in(false),
DellAnimation(false) {}

node::node(const sf::Vector2f &v) : isEmpty(true), isSelected(false), coordinate(v), isMove_inside(true), isPut_in(false),
DellAnimation(false) {}

void node::Blow_Animation()
{
	image_blow.loadFromFile("images/blow.png");
	texture_blow.loadFromImage(image_blow);
	sprite_blow.setTexture(texture_blow);
	sprite_blow.setTextureRect(sf::IntRect(0, 0, 60, 60));
	sprite_blow.setOrigin(30, 30);
	sprite_blow.setPosition(coordinate);

}