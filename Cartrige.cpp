#include"Cartrige.h"

Cartriges::Cartriges(sf::Texture& texture, sf::Vector2f pos)
{
	m_pos = pos;
	m_sprite_obj.setTexture(texture);

}

void Cartriges::CartrigeReload(Player* player)
{
	if (flag_crt) {
		m_sprite_obj.setPosition(m_pos);
		m_sprite_obj.setScale(1.5, 1.5);
		if (m_sprite_obj.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
			player->setCountCartrige(1);
			flag_crt = false;
		}
	}
}
