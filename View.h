#pragma once
#include <SFML/Graphics.hpp>

sf::View view;

sf::View getCameraPosition(sf::Vector2f player_pos) {
	view.setCenter(player_pos.x + 100, player_pos.y);
	return view;
}