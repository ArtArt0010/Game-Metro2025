#pragma once
#include <SFML/Graphics.hpp>
namespace textures {
    sf::Texture player_texture;

    static void Player_setTextures() {
        player_texture.loadFromFile("Texturs/Gamer_spriteSheet2.png");
        
    }
}