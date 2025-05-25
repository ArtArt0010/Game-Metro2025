#include "LevelLoad.h"
#include <fstream>
#include <iostream>

void LevelLoad(const std::string& filename, sf::Texture& tileTexture, std::vector<sf::Sprite>& levelTiles) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error open file";
        return;
    }

    std::string line;
    int y = 0;
    const float tileSize = 32.f * 2;
    while (std::getline(file, line)) {
        for (int x = 0; x < line.size(); ++x) {
            char ch = line[x];
            sf::Vector2f pos(x * tileSize, y * tileSize);

            sf::Sprite tile;
            tile.setTexture(tileTexture);

            switch (ch)
            {
            case ' ':
                tile.setTextureRect(sf::IntRect(0, 0, 32, 32));
                break;
            case '0':
                tile.setTextureRect(sf::IntRect(64, 0, 32, 32));
                break;
            case '1':
                tile.setTextureRect(sf::IntRect(32, 0, 32, 32));
                break;
            case '2':
                tile.setTextureRect(sf::IntRect(128, 0, 32, 32));
                break;
            case '3':
                tile.setTextureRect(sf::IntRect(160, 0, 32, 32));
                break;
            default:
                break;
            }
     

            tile.setPosition(pos);
           tile.setScale(2, 2);
            levelTiles.push_back(tile);
        }
        y++;
    }
}
