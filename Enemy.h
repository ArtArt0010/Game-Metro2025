#pragma once

#include "Character.h"
//#include "Bullet.h"
//class EnemyManager;

#include"Player.h"

class Enemy : public Character {
private:
	

	float timerAtaka = 0.f;
	float AtakaDelay = 0.8;
	sf::Vector2f PlayerPosition;
	bool Dead_animation = false;

	bool Ataka = false;
	bool player_dead = false;
public:
	int my_damage = 5;
	Enemy() = delete;
	Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp);

	~Enemy();

	void Update(float time) override;
	void takeDamage(int dmg);
	void ataka(float time, Player* player);

	void setPlayerPosition(sf::Vector2f& player_pos);

	bool isDead() const;

	bool isIntersection(const sf::Sprite& bull);
};