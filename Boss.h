#pragma once


#include "Character.h"


#include"Player.h"

class Boss : public Character {
private:

	sf::Vector2f m_prevPosition;
	float timerAtaka = 0.f;
	float AtakaDelay = 0.8;
	sf::Vector2f PlayerPosition;
	bool Dead_animation = false;

	bool Ataka = false;
	bool player_dead = false;
public:
	int my_damage;
	Boss() = delete;
	Boss(sf::Texture& texture, sf::Vector2f start_pos, int hp, int damage, float speed, int sprite_size, float animation_speed, float scale);

	~Boss();

	void Update(float time) override;
	void takeDamage(int dmg);
	void ataka(float time, Player* player);

	void setPlayerPosition(sf::Vector2f& player_pos);

	bool isDead() const;

	bool isIntersection(const sf::Sprite& bull);
	void colision(const sf::Sprite& sprite);
};