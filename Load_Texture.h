#pragma once
#include <SFML/Graphics.hpp>
namespace textures {
    sf::Texture player_texture;

    static void Player_setTextures() {
        player_texture.loadFromFile("Texturs/Run_sheet.png");
        
    }
}