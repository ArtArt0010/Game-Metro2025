#pragma once


#include <SFML/Graphics.hpp>


class GameObject {
public:
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Sprite   m_sprite_obj;
	
	GameObject() = default;
    virtual ~GameObject() = default;

public:
	sf::Sprite getSprite() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	
};