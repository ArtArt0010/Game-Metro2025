#pragma once
#include <SFML/Audio.hpp>
#include "Character.h"
//#include "Bullet.h"
//class EnemyManager;

#include"Player.h"
#include"Trains.h"

class Enemy : public Character {
private:
	bool saund_play = false;
	sf::SoundBuffer skorpBuffer;
	sf::Sound skorpSound;

	sf::Vector2f m_prevPosition;
	float timerAtaka = 0.f;
	float AtakaDelay = 0.8;
	sf::Vector2f PlayerPosition;
	bool Dead_animation = false;

	bool Ataka = false;
	bool player_dead = false;
public:
	int my_damage;
	Enemy() = delete;
	Enemy(sf::Texture& texture, sf::Vector2f start_pos, int hp, int damage, float speed, int sprite_size, float animation_speed, float scale);

	~Enemy();

	void Update(float time) override;
	void takeDamage(int dmg);
	void ataka(float time, Player* player);

	void setPlayerPosition(sf::Vector2f& player_pos);

	bool isDead() const;

	bool isIntersection(const sf::Sprite& bull);
	void colisions(const std::vector<Train>& collidables);
};