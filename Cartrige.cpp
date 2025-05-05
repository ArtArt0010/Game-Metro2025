#include"Cartrige.h"

Cartriges::Cartriges(sf::Texture& texture, sf::Vector2f pos)
{
	m_pos = pos;
	m_sprite_obj.setTexture(texture);

}

void Cartriges::CartrigeReload(Player* player)
{
	if (flag_crt) {
		if (m_sprite_obj.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
			player->setCountCartrige(1);
			flag_crt = false;
		}
	}
}
