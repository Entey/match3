#ifndef GAME_ALGORITHM
#define GAME_ALGORITHM

#include "Greed_Element.h"
#include <fstream>

const int n = 8;
using namespace sf;


class Player {
	node grid[n][n];
	node *p[n*n];
	float  level_time;
	int swap_count, score;
	vector<sf::Vector2f> coord;
	float x;
	float y;
	bool isMove;
	sf::RectangleShape *LineTime;
	float angle, frame;
	sf::Vector2i pixelPos; // для захвату курсора
	sf::Vector2f pos;  // для визначення позиції курсору
	int isPosibleSwap; // перевірка можливості ходу
	vector<node*> vec_for_dell;
	vector<node*>::iterator it_dell;
public:
	Player() : isMove(false), isPosibleSwap(0), score(0), swap_count(10), level_time(100.0), frame(0) { // create coordinate for view

		generation_greed();

		LineTime = new sf::RectangleShape;
		LineTime->setSize(sf::Vector2f(level_time, 10));
		LineTime->setOrigin(level_time, 10);
		LineTime->setFillColor(sf::Color(10, 250, 150));
		LineTime->setPosition(sf::Vector2f(510, 150));
	}

	const void generation_greed(){
		x = y = 50;
		while (y <= 400)
		{
			while (x <= 400)
			{
				coord.push_back(sf::Vector2f(x, y));
				x += 50;
			}
			x = 50;
			y += 50;
		}


		int z = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				grid[i][j] = node(coord[z]);
				p[z] = &grid[i][j];
				grid[i][j].Blow_Animation();
				z++;
			}
	}

	void swap(node& left, node &right){
		node swa;
		swa.element = left.element;
		left.element = right.element;
		right.element = swa.element;
	}


	void check_startline(){
		for (int i = 0; i < n; i++)
			if (grid[0][i].isEmpty == true)
			{
				grid[0][i].Create_element();
				grid[0][i].isEmpty = false;
			}
	}

	void DropDown(float time) {
		for (int i = 0; i<n - 1; i++)
			for (int j = 0; j<n; j++)
			{
				if (grid[i][j].isEmpty == false && grid[i + 1][j].isEmpty == true)
				{
					isMove = true; grid[i][j].isMove_inside = true;
					grid[i][j].element->sprite.move(0, time*0.1);
					if (grid[i][j].element->sprite.getPosition().y > grid[i + 1][j].coordinate.y)
					{
						grid[i + 1][j].element = grid[i][j].element;

						grid[i][j].element = nullptr;
						grid[i][j].isEmpty = true;
						grid[i + 1][j].isEmpty = false;
						isMove = false;
						grid[i][j].isMove_inside = false;
					}
				}
				if (grid[7][j].isEmpty == false)
					grid[7][j].isMove_inside = false;
			}
	}

	void Swap(float time) {
		for (int i = 0; i<n; i++)
			for (int j = 0; j<n; j++)
			{	// перевірка на swap елементів по горизонталі
				if (grid[i][j].isSelected && grid[i][j + 1].isSelected  && j < 7 && isPosibleSwap == 2)
				{
					isMove = true;
					grid[i][j].element->sprite.move(time*0.1, 0);
					grid[i][j + 1].element->sprite.move(time*-0.1, 0);
					{
						if (grid[i][j].element->sprite.getPosition().x > grid[i][j + 1].coordinate.x)
						{
							swap(grid[i][j], grid[i][j + 1]);
							isMove = false;
							grid[i][j].isSelected = false;
							grid[i][j + 1].isSelected = false;
							grid[i][j].element->sprite.setScale(1.0, 1.0);
							grid[i][j + 1].element->sprite.setScale(1.0, 1.0);
							isPosibleSwap = 0;
							swap_count--;
						} }
				}
				else if (grid[i][j].isSelected && grid[i + 1][j].isSelected && i < 7 && isPosibleSwap == 2) { // перевірка на swap елементів по вертикалі
					isMove = true;
					grid[i][j].element->sprite.move(0, time*0.1);
					grid[i + 1][j].element->sprite.move(0, time*-0.1);
					{
						if (grid[i][j].element->sprite.getPosition().y > grid[i + 1][j].coordinate.y)
						{
							swap(grid[i][j], grid[i + 1][j]);
							isMove = false;
							grid[i][j].isSelected = false;
							grid[i + 1][j].isSelected = false;
							grid[i][j].element->sprite.setScale(1.0, 1.0);
							grid[i + 1][j].element->sprite.setScale(1.0, 1.0);
							swap_count--;
						} }
				}
				else //zroj ж не знайдені варіанти або хід не правельний скидуємо виділення
					if (isPosibleSwap > 2) {
						for (int i = 0; i<n; i++)
							for (int j = 0; j<n; j++)
							{
								grid[i][j].isSelected = false;
								grid[i][j].element->sprite.setScale(1.0, 1.0);
							}
						isPosibleSwap = 0;
					}
			}
	}

	void TimeLine(float time, sf::RenderWindow & window, int choice = 1){

		LineTime->setPosition(sf::Vector2f(670, 200));
		switch (choice){
		case 1:{
			level_time = level_time - time*0.001;
			LineTime->setOrigin(level_time, 10);
			LineTime->setSize(sf::Vector2f(level_time, 10));
		} break;
		case 2:{
			LineTime->setOrigin(swap_count, 10);
			LineTime->setSize(sf::Vector2f(swap_count, 10));
		}break;

		}

		window.draw(*LineTime);
	}

	void Graphics(float time, sf::RenderWindow & window) {

		angle = 0.3*time;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {

				if (grid[i][j].isSelected == true && grid[i][j].isEmpty == false)
					grid[i][j].element->sprite.rotate(angle);
				if (grid[i][j].DellAnimation == true)
				{
					if (frame < 3) {
						frame += time*0.01;
						grid[i][j].sprite_blow.setTextureRect(sf::IntRect(60 * int(frame), 0, 60, 60));
						window.draw(grid[i][j].sprite_blow);
					}
					else {
						grid[i][j].DellAnimation = false;
						frame = 0;
					}
				}
			}
	}

	void ClicMouse(sf::Event &ev, sf::RenderWindow &window) {
		pixelPos = sf::Mouse::getPosition(window);
		pos = window.mapPixelToCoords(pixelPos);
		if (isMove == false && swap_count > 0)
			if (ev.type == sf::Event::MouseButtonPressed)
				if (ev.key.code == sf::Mouse::Button::Left)
				{
					for (int i = 0; i < n; i++)
						for (int j = 0; j < n; j++)
							if (grid[i][j].element->sprite.getGlobalBounds().contains(pos.x, pos.y))
							{
								grid[i][j].isSelected = true;
								grid[i][j].element->sprite.setScale(1.1, 1.1);
								isPosibleSwap++;
							}
				}
	}

	void Check_line()  // перевірка ліній на видалення 3 та більше елементів
	{
		int z;
		for (int i = 7; i >= 0; i--)
			for (int j = 7; j > 1; j--) {
				if (grid[i][j].isMove_inside == false &&
					grid[i][j - 1].isMove_inside == false &&
					grid[i][j - 2].isMove_inside == false &&
					grid[i][j].isEmpty == false &&
					grid[i][j - 1].isEmpty == false &&
					grid[i][j - 2].isEmpty == false &&
					grid[i][j].element->choice == grid[i][j - 1].element->choice &&
					grid[i][j].element->choice == grid[i][j - 2].element->choice) {

					if (grid[i][j].isPut_in == false) {
						vec_for_dell.push_back(&grid[i][j]); grid[i][j].isPut_in == true;
					}
					if (grid[i][j - 1].isPut_in == false) {
						vec_for_dell.push_back(&grid[i][j - 1]); grid[i][j - 1].isPut_in == true;
					}
					if (grid[i][j - 2].isPut_in == false) {
						vec_for_dell.push_back(&grid[i][j - 2]); grid[i][j - 2].isPut_in == true;
					}
					z = j - 3;
					while (z >= 7) {
						if (grid[i][j].element->choice == grid[i][z].element->choice
							&& grid[i][z].isMove_inside == false
							&& grid[i][z].isPut_in == false) {
							vec_for_dell.push_back(&grid[i][z]);
							grid[i][z].isPut_in == true;
							z--;
						}
						else break;
					}
				}
				else continue;
			}

		for (int i = 7; i > 1; i--)
			for (int j = 7; j >= 0; j--) {
				if (grid[i][j].isMove_inside == false &&
					grid[i - 1][j].isMove_inside == false &&
					grid[i - 2][j].isMove_inside == false &&
					grid[i][j].isEmpty == false &&
					grid[i - 1][j].isEmpty == false &&
					grid[i - 2][j].isEmpty == false &&
					grid[i][j].element->choice == grid[i - 1][j].element->choice &&
					grid[i][j].element->choice == grid[i - 2][j].element->choice) {
					if (grid[i][j].isPut_in == false) {
						vec_for_dell.push_back(&grid[i][j]); grid[i][j].isPut_in = true;
					}
					if (grid[i - 1][j].isPut_in == false) {
						vec_for_dell.push_back(&grid[i - 1][j]); grid[i - 1][j].isPut_in = true;
					}
					if (grid[i - 2][j].isPut_in == false) {
						vec_for_dell.push_back(&grid[i - 2][j]); grid[i - 2][j].isPut_in = true;
					}
					z = i - 3;
					while (z >= 7) { // додаткова перевірк для рядків більше 3 елементів
						if (grid[i][j].element->choice == grid[z][j].element->choice
							&& grid[z][j].isMove_inside == false
							&& grid[z][j].isPut_in == false) {
							vec_for_dell.push_back(&grid[z][j]);
							grid[z][j].isPut_in == true;
							z--;
						}
						else break;
					}
				}
				else continue;
			}


		for (int i = 0; i < vec_for_dell.size(); i++){
			vec_for_dell[i]->DellAnimation = true;
			vec_for_dell[i]->element = nullptr;
			vec_for_dell[i]->Del_element();
			vec_for_dell[i]->isEmpty = true;
			vec_for_dell[i]->isPut_in = false;
			score += 10;
		}

		vec_for_dell.erase(vec_for_dell.begin(), vec_for_dell.end());  // очищаємо вектор				
	}

	void show(sf::RenderWindow &window) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (grid[i][j].isEmpty == false)
					window.draw(grid[i][j].draww());
	}
	int getSwapCount() { return swap_count; }
	int getScore() { return score; }
	int GetSwapCount() { return swap_count; }
};


#endif GAME_ALGORITHM