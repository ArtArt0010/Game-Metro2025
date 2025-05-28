#include "Trains.h"


Train::Train(sf::Texture& texture, sf::Vector2f pos)
{
	
	m_sprite_obj.setTexture(texture);
	m_pos.x = pos.x;
	m_pos.y = pos.y;



}

void Train::Update(float time)
{
	

	m_sprite_obj.setPosition(m_pos);
	m_sprite_obj.setScale(6.f, 6.f);
	
}

bool Train::isIntersection(const sf::Sprite& bull)
{
	if (m_sprite_obj.getGlobalBounds().intersects(bull.getGlobalBounds())) {
		//std::cout << 1;
		return true;
	}

	return false;
}