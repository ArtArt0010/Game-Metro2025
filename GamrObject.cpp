#include "GameObject.h"

sf::Sprite GameObject::getSprite() const {
    return m_sprite_obj;
}

sf::Vector2f GameObject::getPosition() const {
    return m_pos;
}

sf::Vector2f GameObject::getSize() const {
    return m_size;
}