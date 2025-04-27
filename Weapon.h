#pragma once
#include <SFML/Graphics.hpp>
#include"Player.h"
enum class Direction_weapon : bool {
	LEFT = 0,
	RIGHT = 1
};

class Weapon {
protected:
	int m_cartridges;
	float m_shooting_speed;
	sf::Vector2f m_size_weapon;
	sf::Vector2f m_Position_weapon;
	sf::Sprite m_sprite_weapon;
	Direction_weapon    m_direction_weapon = Direction_weapon::RIGHT;
	sf::Vector2f direction_mause;
	//настройки анимации
	int m_frameWidth_w;
	int m_frameHeight_w;
	int m_numFrames_w;
	int m_currentFrame_w;
	float m_animationSpeed_w;
	float m_elapsedTime_w;


public:
	virtual ~Weapon();
	virtual void Update_weapon(float time, Player* player, sf::RenderWindow& window) = 0;

	void setPosition(sf::Vector2f& pos);
	void setDirection(Direction_weapon direction);
	void setRotation(float angle);
	void setOrigen(float x, float y);
	void setScale(float x, float y);
	void setDirectionMause(sf::Vector2f& dirM);

	int getCartridges() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	sf::Vector2f getDirectionMausse()const;

	Direction_weapon getDirection() const;

};