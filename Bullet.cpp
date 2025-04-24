#include "Bullet.h"
#include "Load_Texture.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f direction)
{
	float len = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (len != 0){
		m_direction /= len;
	}
	m_sprite.setTexture(textures::bullet_texture);
	m_pos = pos;
	//m_direction = direction;
	m_damage = 5;
}

void Bullet::Update(float time)
{
	m_pos.x += m_direction.x * speed * time;
	m_pos.y += m_direction.y * speed * time;

	m_sprite.setPosition(m_pos);
	m_sprite.setScale(0.5, 0.5);
}

void Bullet::updateDamage()
{
}
