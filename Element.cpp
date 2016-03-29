#include "Element.h"

Element::Element(const sf::Vector2f &coord) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> one_to_five{ 1, 5 };
	choice = one_to_five(gen);
	texture.loadFromImage(choice_image(choice));
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	sprite.setOrigin(25, 25);
	sprite.setPosition(coord);
}

static const sf::Image choice_image(int choice) {
	static bool t = false;
	static sf::Image im1;
	static sf::Image im2;
	static sf::Image im3;
	static sf::Image im4;
	static sf::Image im5;
	if (!t) {
		im1.loadFromFile("images/1.png");
		im2.loadFromFile("images/2.png");
		im3.loadFromFile("images/3.png");
		im4.loadFromFile("images/4.png");
		im5.loadFromFile("images/5.png");
		t = true;
	}
	switch (choice)
	{
	case 1: return im1; break;
	case 2: return im2; break;
	case 3: return im3; break;
	case 4: return im4; break;
	case 5: return im5; break;
	}
}