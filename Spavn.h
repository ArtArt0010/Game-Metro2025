#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Constants.h"
#include "Cartrige.h"
#include "Trains.h"
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


		enemys.emplace_back(texture, sf::Vector2f(x, y), 30, 5, 250.f, 32, 0.08, 3.f);

		
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
//void spawnTrain(int min_count, int max_count, std::vector<Train>& trains, sf::Texture& texture, float y) {
//	int count = rand() % (max_count - min_count + 1) + min_count;
//
//	int buff_x = 0;
//	for (int i = 0; i < count; i++) {
//
//		int x = rand() % ((Widht_x - 1500) - 400 + 1) + 400;
//		
//
//		int ampt = 0;
//		while ((abs(buff_x - x) <2000) && ampt < 60) {
//			x = rand() % ((Widht_x - 1500) - 400 + 1) + 400;
//		;
//			ampt++;
//		}
//
//		buff_x = x;
//		
//
//
//		trains.emplace_back(texture, sf::Vector2f(x, y));
//
//	}
//
//
//}
//void spawnTrain(int min_count, int max_count, std::vector<Train>& trains, sf::Texture& texture, float y) {
//	int count = rand() % (max_count - min_count + 1) + min_count;
//
//	for (int i = 0; i < count; ++i) {
//		int x = 0;
//		bool valid = false;
//		int attempts = 0;
//
//		while (!valid && attempts < 100) {
//			x = rand() % ((Widht_x - 1500) - 300 + 1) + 300;
//			valid = true;
//
//			for (const auto& train : trains) {
//				if (std::abs(train.getPosition().x - x) < 500.f) { // минимальная дистанция
//					valid = false;
//					break;
//				}
//			}
//
//			attempts++;
//		}
//
//		if (valid) {
//			trains.emplace_back(texture, sf::Vector2f(x, y));
//		}
//	}
//}
void spawnTrain(int min_count, int max_count, std::vector<Train>& trains, sf::Texture& texture, float y) {
	int count = rand() % (max_count - min_count + 1) + min_count;

float minSeparation = 182*6 + 800.f; // хотим не менее 50px между краями

for (int i = 0; i < count; ++i) {
	bool placed = false;
	int attempts = 0;
	const int MAX_ATTEMPTS = 100;

	while (!placed && attempts < MAX_ATTEMPTS) {
		++attempts;
		int x = rand() % ((Widht_x - 1500) - 400 + 1) + 400;

		// проверяем, что новая позиция не ближе minSeparation
		bool ok = true;
		for (auto& t : trains) {
			float existingX = t.getSprite().getPosition().x;
			if (std::abs(existingX - x) < minSeparation) {
				ok = false;
				break;
			}
		}

		if (ok) {
			trains.emplace_back(texture, sf::Vector2f(x, y));
			placed = true;
		}
	}

	// Если после MAX_ATTEMPTS не удалось найти место — просто пропускаем этот спавн
	if (!placed) {
		std::cerr << "Warning: could not place train #" << i << "\n";
	}
}
}