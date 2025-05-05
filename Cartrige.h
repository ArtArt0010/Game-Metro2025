#pragma once
#include "GameObject.h"
#include "Player.h"

class Cartriges : public GameObject {
private:
	bool flag_crt = true;
public:
	Cartriges(sf::Texture& texture, sf::Vector2f pos);
	void CartrigeReload(Player* player);

};