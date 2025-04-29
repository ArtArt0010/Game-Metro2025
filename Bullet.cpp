#include "Bullet.h"


Bullet::Bullet(sf::Texture& texture, sf::Vector2f pos, sf::Vector2f direction)
{
	float len = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (len != 0) {
		m_direction = direction / len;
	}
	else {
		m_direction = { 1.f, 0.f }; 
	}
	m_sprite_obj.setTexture(texture);
	m_pos.x = pos.x;
	m_pos.y = pos.y - 9;


	m_damage = 5;
}

void Bullet::Update(float time)
{
	m_pos.x += m_direction.x * speed * time;
	m_pos.y += m_direction.y * speed * time;

	m_sprite_obj.setPosition(m_pos);
	m_sprite_obj.setScale(0.8, 0.8);
	lifeTime -= 0.01;
}

void Bullet::updateDamage()
{
}

bool Bullet::isAlife() const
{
	return lifeTime > 0.f;
}
