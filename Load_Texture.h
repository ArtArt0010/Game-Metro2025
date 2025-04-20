#pragma once
#include <SFML/Graphics.hpp>
namespace textures {
    sf::Texture player_texture;

    static void Player_setTextures() {
        player_texture.loadFromFile("Texturs/Gamer_spriteSheet3.png");
        
    }
    sf::Texture automat_texture;

    static void Automat_texture() {
        automat_texture.loadFromFile("Texturs/Automate.png");

    }

}