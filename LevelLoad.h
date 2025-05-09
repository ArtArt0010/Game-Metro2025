#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "Player.h"
#include "Enemy.h"
#include "Cartrige.h"

void LevelLoad(const std::string& filename, sf::Texture& tileTexture, std::vector<sf::Sprite>& levelTiles);