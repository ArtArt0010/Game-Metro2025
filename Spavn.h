#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Constants.h"
#include "Cartrige.h"
void spawnEnemy(int min_count, int max_count, std::vector<Enemy>& enemys, sf::Texture& texture) {
	
	int count_enemy = rand() % (max_count - min_count + 1) + min_count;

	int buff_x = 0;
	int buff_y = 0;

	for (int i = 0; i < count_enemy; i++) {
		
		int x = rand() % (Widht_x - 124 + 1) + 124;
		int y = rand() % (Height_y - 40 + 1) + 40;

		int ampt = 0;
		while ((abs(buff_x - x) < 400 || abs(buff_y - y) < 400) && ampt < 50) {
			x = rand() % (Widht_x - 248 + 1) + 248;
		    y = rand() % (Height_y - 80 + 1) + 80;
			ampt++;
		}

		buff_x = x;
		buff_y = y;


		enemys.emplace_back(texture, sf::Vector2f(x, y), 50, 5, 250.f, 32, 0.08, 3.f);

		
	}


}

void spawnCartriges(int min_count, int max_count, std::vector<Cartriges>& cartrige, sf::Texture& texture) {
	int count_enemy = rand() % (max_count - min_count + 1) + min_count;

	int buff_x = 0;
	int buff_y = 0;

	for (int i = 0; i < count_enemy; i++) {

		int x = rand() % (Widht_x - 124 + 1) + 124;
		int y = rand() % (Height_y - 40 + 1) + 40;

		int ampt = 0;
		while ((abs(buff_x - x) < 200 || abs(buff_y - y) < 200) && ampt < 50) {
			x = rand() % (Widht_x - 248 + 1) + 248;
			y = rand() % (Height_y - 80 + 1) + 80;
			ampt++;
		}

		buff_x = x;
		buff_y = y;


		cartrige.emplace_back(texture, sf::Vector2f(x, y));

	}
}