#pragma once
#include "Character.h"
#include "Constants.h"


class PlayerController;

enum class State {
	IDLE,
	RUN
};

class Player : public Character {
private:
	State m_state;
	PlayerController* m_controller;

	sf::Vector2f m_prevPosition;
public:
	int count_dead_enemy = 0;
	int count_cartrige = 1;
	bool is_Dead = false;
	Player() = delete;
	Player(sf::Texture& texture, sf::Vector2f start_pos, int hp);
	
	~Player();

	void Update(float time) override;
	void setState(State state);
	void restrictions();

	void setCountCartrige(int c_cartrige);
	int getCountCartrige();
	bool is_Life();
	void setLife(bool Life);
	void colisions(const std::vector<sf::Sprite>& collidables, float time);

	void colision(const sf::Sprite& sprite);
	State getState();
};