#pragma once
#include "GameObject.h"
class Train : public GameObject {
private:
	sf::Vector2f m_direction;

	sf::Vector2f m_pos;


public:
	int m_damage;
	Train(sf::Texture& texture, sf::Vector2f pos);
	void Update(float time);

};