#pragma once

#include "Character.h"
//#include "Bullet.h"
//class EnemyManager;



class Enemy : public Character {
private:
	


	sf::Vector2f PlayerPosition;
	bool Dead_animation = false;

	bool Ataka = false;

public:
	int my_damage = 5;
	Enemy() = delete;
	Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp);

	~Enemy();

	void Update(float time) override;
	void takeDamage(int dmg);
	void ataka(float time);

	void setPlayerPosition(sf::Vector2f& player_pos);

	bool isDead() const;

	bool isIntersection(const sf::Sprite& bull);
};