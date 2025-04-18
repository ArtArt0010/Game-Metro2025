#pragma once
#include <SFML/Graphics.hpp>

enum class Direction : bool {
	LEFT = 0,
	RIGHT = 1
};

class Character {
protected:
	int m_hp; 
	float m_speed;
	sf::Vector2f m_size;
	sf::Vector2f m_Position;
	sf::Sprite m_sprite;
	Direction    m_direction = Direction::RIGHT;

	//��������� ��������
	int m_frameWidth;
	int m_frameHeight;
	int m_numFrames;
	int m_currentFrame;
	float m_animationSpeed;
	float m_elapsedTime;

	
public:
	virtual ~Character();
	virtual void Update(float time) = 0;
	void take_Damage(int damage);
	void setPosition(sf::Vector2f& pos);
	void setDirection(Direction direction);

	float getHP() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	Direction getDirection() const;

};