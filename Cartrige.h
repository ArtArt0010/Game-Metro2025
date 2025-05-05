#pragma once
#include "GameObject.h"
#include "Player.h"

class Cartriges : public GameObject {
private:
	
public:
	bool flag_crt = true;
	Cartriges(sf::Texture& texture, sf::Vector2f pos);
	void CartrigeReload(Player* player);

};