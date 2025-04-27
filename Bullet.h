#pragma once

#include "GameObject.h"

class Bullet : public GameObject {
private:
	sf::Vector2f m_direction;
	int m_damage;
	sf::Vector2f m_pos;
	float speed = 500.f;
	float lifeTime = 5;

public:

	Bullet(sf::Texture& texture, sf::Vector2f pos, sf::Vector2f direction);
	void Update(float time);
	void updateDamage();
	bool isAlife() const;
};