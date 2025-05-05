#pragma once
#include "Character.h"

class PlayerController;

enum class State {
	IDLE,
	RUN
};

class Player : public Character {
private:
	State m_state;
	PlayerController* m_controller;

public:
	int count_cartrige = 0;
	Player() = delete;
	Player(sf::Texture& texture, sf::Vector2f start_pos, int hp);
	
	~Player();

	void Update(float time) override;
	void setState(State state);

	void setCountCartrige(int c_cartrige);
	int getCountCartrige();
	

};