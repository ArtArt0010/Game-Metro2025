#include "Character.h"
//#include "iostream"

Character::~Character() {}

void Character::take_Damage(int damage)
{
	m_hp -= damage;

	//std::cout << m_hp << " ";
}

void Character::setPosition(sf::Vector2f& pos)
{
	m_Position = pos;
}

void Character::setDirection(Direction direction)
{
	m_direction = direction;
}

float Character::getHP() const
{
	return m_hp;
}

sf::Vector2f Character::getSize() const
{
	return m_size;
}

sf::Vector2f Character::getPosition() const
{
	return m_Position;
}

sf::Sprite Character::getSprite() const
{
	return m_sprite;
}

Direction Character::getDirection() const
{
	return m_direction;
}





