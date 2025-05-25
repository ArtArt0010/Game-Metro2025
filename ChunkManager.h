#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include<unordered_map>

const sf::Vector2f chunk_size = {Tile_size * chunk_tiles,Tile_size * chunk_tiles};

using ChankID = std::pair<int, int>;

struct ChunkIdHash {
    std::size_t operator()(ChankID const& c) const {
        return std::hash<int>()(c.first * 73856093 ^ c.second * 19349663);
    }
};


struct Chunk {
    ChankID id;
    std::vector<sf::Sprite> tiles;
};

class ChankManager
{
    sf::Texture& m_tileTexture;
    std::unordered_map<ChankID, Chunk, ChunkIdHash> m_loadedChunks;
public:
	ChankManager(sf::Texture& tileTexture): m_tileTexture(tileTexture){}



    static ChankID worldToChunk(sf::Vector2f worldPos);

    void loadChunk(ChankID id);

	~ChankManager();



};

