#include "Weapon.h"

Weapon::~Weapon() {}



void Weapon::setPosition(sf::Vector2f& pos)
{
	m_Position_weapon = pos;
	m_sprite_weapon.setPosition(pos);
}

void Weapon::setDirection(Direction_weapon direction)
{
	m_direction_weapon = direction;

}

int Weapon::getCartridges() const
{
	return m_cartridges;
}

sf::Vector2f Weapon::getSize() const
{
	return m_size_weapon;
}

sf::Vector2f Weapon::getPosition() const
{
	return m_Position_weapon;
}

sf::Sprite Weapon::getSprite() const
{
	return m_sprite_weapon;
}

sf::Vector2f Weapon::getDirectionMausse() const
{
	return direction_mause;
}

Direction_weapon Weapon::getDirection() const
{
	return m_direction_weapon;
}
void Weapon::setRotation(float angle) {
	m_sprite_weapon.setRotation(angle);
}

void Weapon::setOrigen(float x, float y)
{
	m_sprite_weapon.setOrigin(x, y);
}

void Weapon::setScale(float x, float y) {
	m_sprite_weapon.setScale(x, y);
	
}

void Weapon::setDirectionMause(sf::Vector2f& dirM)
{
	direction_mause = dirM;
}

void Weapon::setCartriges(int crt)
{
	m_cartridges = crt;
}


