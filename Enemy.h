#pragma once

#include "Character.h"

class EnemyManager;



class Enemy : public Character {
private:
	
	EnemyManager* m_EnemyManager;

public:
	Enemy() = delete;
	Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp);

	~Enemy();

	void Update(float time) override;
	

};