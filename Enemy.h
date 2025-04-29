#pragma once

#include "Character.h"

class EnemyManager;



class Enemy : public Character {
private:
	
	EnemyManager* m_EnemyManager;
	int my_damage = 5;
	sf::Vector2f PlayerPosition;

public:
	Enemy() = delete;
	Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp);

	~Enemy();

	void Update(float time) override;
	void takeDamage(int dmg);
	void ataka(int dmg);

	void setPlayerPosition(sf::Vector2f& player_pos);

	bool isDead() const;

};