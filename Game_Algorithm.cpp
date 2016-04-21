#include "Resources\Game_Algorithm.h"
#include <memory>
Player::Player() : isMove(false), isPosibleSwap(0), score(0), swap_count(1), frame(0) { // create coordinate for view
	Generation_Greed();
	cursor_texture.loadFromFile("images/cursor.png");
	cursor.setTexture(cursor_texture);
}

void Player::Generation_Greed() {
	x = y = 50;
	while (y <= 400) {
	while (x <= 400) {
		coord.push_back(sf::Vector2f(x, y));
		x += 50;
		}
		x = 50;
		y += 50;
	}
	int z = 0;
	// ініціалізація
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) {
			grid[i][j] = node(coord[z++]);
			grid[i][j].Blow_Animation(); // завантаження спрайтів анімації
		}
}

void Player::Swap(node& left, node &right){
	node swa;
	swa.element = left.element;
	left.element = right.element;
	right.element = swa.element;
}


void Player::Check_Startline(){
	for (int i = 0; i < n; i++)
		if (grid[0][i].isEmpty == true) {
			grid[0][i].Create_element();
			grid[0][i].isEmpty = false;
		}
}

void Player::DropDown(const float &time) {
	for (int i = 0; i<n - 1; i++)
	for (int j = 0; j<n; j++) {
			if (grid[i][j].isEmpty == false && grid[i + 1][j].isEmpty == true) {
				isMove = true; grid[i][j].isMove_inside = true;
				grid[i][j].element->sprite.move(0, time*0.15);
				if (grid[i][j].element->sprite.getPosition().y > grid[i + 1][j].coordinate.y) {
					grid[i + 1][j].element = grid[i][j].element;
					grid[i][j].element = nullptr;
					grid[i][j].isEmpty = true;
					grid[i + 1][j].isEmpty = false;
					isMove = false;
					grid[i][j].isMove_inside = false;
				}
			}
			if (grid[7][j].isEmpty == false)
				grid[7][j].isMove_inside = false; // щоб не провалювались з останнього рядку
		}
}

void Player::Swap_Elements(const float &time) {
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) {	
			if (grid[i][j].isSelected && grid[i][j + 1].isSelected  && j < 7 && isPosibleSwap == 2) { // перевірка на swap елементів по горизонталі
				isMove = true;
				grid[i][j].element->sprite.move(time*0.1, 0);
				grid[i][j + 1].element->sprite.move(time*-0.1, 0);
					if (grid[i][j].element->sprite.getPosition().x > grid[i][j + 1].coordinate.x) {
						Swap(grid[i][j], grid[i][j + 1]);
						isMove = false;
						grid[i][j].isSelected = false;
						grid[i][j + 1].isSelected = false;
						grid[i][j].element->sprite.setScale(1.0, 1.0);
						grid[i][j + 1].element->sprite.setScale(1.0, 1.0);
						isPosibleSwap = 0;
						swap_count--;
					} 
			}
			else if (grid[i][j].isSelected && grid[i + 1][j].isSelected && i < 7 && isPosibleSwap == 2) { // перевірка на swap елементів по вертикалі
				isMove = true;
				grid[i][j].element->sprite.move(0, time*0.1);
				grid[i + 1][j].element->sprite.move(0, time*-0.1);
					if (grid[i][j].element->sprite.getPosition().y > grid[i + 1][j].coordinate.y) {
						Swap(grid[i][j], grid[i + 1][j]);
						isMove = false;
						grid[i][j].isSelected = false;
						grid[i + 1][j].isSelected = false;
						grid[i][j].element->sprite.setScale(1.0, 1.0);
						grid[i + 1][j].element->sprite.setScale(1.0, 1.0);
						swap_count--;
					} 
			}
			else //якщо ж не знайдені варіанти або хід не правельний скидуємо виділення
				if (isPosibleSwap > 2) {
					for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++) {
							grid[i][j].isSelected = false;
							grid[i][j].element->sprite.setScale(1.0, 1.0);
						}
					isPosibleSwap = 0;
				}
		}
}


void Player::Graphics_Blow(float time, sf::RenderWindow & window) {
	angle = 0.3*time;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++) { 
			//if (grid[i][j].isSelected == true && grid[i][j].isEmpty == false)
			//	grid[i][j].element->sprite.rotate(angle);
			if (grid[i][j].DellAnimation == true) {
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

void Player::ClicMouse(const sf::Event &ev, sf::RenderWindow &window) {
	pixelPos = sf::Mouse::getPosition(window);
	pos = window.mapPixelToCoords(pixelPos);

	if(isSelectedHum && hum_bonus > 0) cursor.setPosition(pos.x, pos.y);
	else window.setMouseCursorVisible(true);
		
	
		if (ev.type == sf::Event::MouseButtonPressed)
		if (ev.key.code == sf::Mouse::Button::Left) {

				if (hum_bonus > 0) { // вкл./викл. молоток (курсор)
					if (area_hum.getGlobalBounds().contains(pos.x, pos.y) && !isSelectedHum) { 
						isSelectedHum = true; window.setMouseCursorVisible(false);
					}
					else if (area_hum.getGlobalBounds().contains(pos.x, pos.y) && isSelectedHum) { 
						isSelectedHum = false; window.setMouseCursorVisible(true);
					}
				}
				else isSelectedHum = false;
				
				if (!isMove && color_bonus >= 3 && area_col.getGlobalBounds().contains(pos.x, pos.y)) {
					isPushedColBon = true; // активація кнопки видалення рандомного кольору
				}

				for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++) {
							if (!isMove && !grid[i][j].isSelected && !isSelectedHum && swap_count > 0 && grid[i][j].element->sprite.getGlobalBounds().contains(pos.x, pos.y)) { // обмін
								isPosibleSwap++;
								grid[i][j].isSelected = true;
								grid[i][j].element->sprite.setScale(1.1, 1.1);
								
							}
							if (!grid[i][j].isEmpty && !grid[i][j].isMove_inside && isSelectedHum &&  grid[i][j].element->sprite.getGlobalBounds().contains(pos.x, pos.y)) { //молоток
								grid[i][j].DellAnimation = true;
								grid[i][j].element = nullptr;
								grid[i][j].isEmpty = true;
								score += 2;
								hum_bonus--;
							}
							
					}
			}
}

void Player::Check_line() { // перевірка ліній на видалення 3 та більше елементів
	for (int i = 7; i >= 0; i--)
	for (int j = 7; j > 1; j--) {
		// по горизонталі
			if (grid[i][j].isMove_inside == false &&
				grid[i][j - 1].isMove_inside == false &&
				grid[i][j - 2].isMove_inside == false &&
				grid[i][j].isEmpty == false &&
				grid[i][j - 1].isEmpty == false &&
				grid[i][j - 2].isEmpty == false &&
				grid[i][j].element->choice == grid[i][j - 1].element->choice &&
				grid[i][j].element->choice == grid[i][j - 2].element->choice) {
					if (!grid[i][j].isPut_in) {
						vec_for_dell.push_back(&grid[i][j]);	 grid[i][j].isPut_in = true;
					}
					if (!grid[i][j - 1].isPut_in) {
						vec_for_dell.push_back(&grid[i][j - 1]); grid[i][j - 1].isPut_in = true;
					}
					if (!grid[i][j - 2].isPut_in) {
						vec_for_dell.push_back(&grid[i][j - 2]); grid[i][j - 2].isPut_in = true;
					}
			} // по вертикалі
			else if (grid[j][i].isMove_inside == false &&
					grid[j - 1][i].isMove_inside == false &&
					grid[j - 2][i].isMove_inside == false &&
					grid[j][i].isEmpty == false &&
					grid[j- 1][i].isEmpty == false &&
					grid[j - 2][i].isEmpty == false &&
					grid[j][i].element->choice == grid[j - 1][i].element->choice &&
					grid[j][i].element->choice == grid[j - 2][i].element->choice) {
						if (!grid[j][i].isPut_in) {
							vec_for_dell.push_back(&grid[j][i]); grid[j][i].isPut_in = true;
						}
						if (!grid[j - 1][i].isPut_in) {
							vec_for_dell.push_back(&grid[j - 1][i]); grid[j - 1][i].isPut_in = true;
						}
						if (!grid[j - 2][i].isPut_in) {
							vec_for_dell.push_back(&grid[j - 2][i]); grid[j - 2][i].isPut_in = true;
						}
				}
			else continue;
			}
	if (vec_for_dell.size() >= 4) hum_bonus++;
	if (vec_for_dell.size() >= 3) color_bonus++;
	for (auto i : vec_for_dell) {
		i->DellAnimation = true;
		i->element = nullptr;
		i->isEmpty = true;
		i->isPut_in = false;
		score += 10;
	}
	vec_for_dell.clear();  // очищаємо вектор	

}

void Player::Show(sf::RenderWindow &window) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (grid[i][j].isEmpty == false)
				window.draw(grid[i][j].draww());
	if (isSelectedHum && hum_bonus) window.draw(cursor);
}

void Player::setColorBonus() {
	if (!bWhitch_col && color_bonus >= 3) {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> one_to_five{ 1, 5 };
		whitch_col = one_to_five(gen);
		bWhitch_col = true;
	}

	if (isPushedColBon) { // видалення елементів з однаковим кольором
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				if (!isMove && grid[i][j].element->choice == whitch_col) {
					grid[i][j].DellAnimation = true;
					grid[i][j].isEmpty = true;
					grid[i][j].element = nullptr;
					color_bonus = 0;
				}
			}
		bWhitch_col = false;
		isPushedColBon = false;
	}
}

int Player::getSwapCount() { return swap_count; }
int Player::getScore() { return score; }
int Player::getHumBunus() {	return hum_bonus; }
int Player::getColBonus() {	return color_bonus; }
int Player::get_Color() { return whitch_col; }
bool Player::getIsMove() { return isMove; }