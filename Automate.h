#pragma once
#pragma once
#include "Weapon.h"

class AutomatController;

enum class State_w {
	SHOOTING,
	STOP
};

class Automat : public Weapon {
private:
	State_w m_state;
	AutomatController* m_controller;

public:
	Automat() = delete;
	Automat(sf::Texture& texture, sf::Vector2f start_pos, int cartridges);

	~Automat();

	void Update_weapon(float time, Player* player, sf::RenderWindow& window) override;
	void setState(State_w state);

	State_w getState();

};