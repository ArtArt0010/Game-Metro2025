#include"ChunkManager.h"

ChankID ChankManager::worldToChunk(sf::Vector2f worldPos)
{
    int cx = int(std::floor(worldPos.x / chunk_size.x));
    int cy = int(std::floor(worldPos.y / chunk_size.y));
    return { cx, cy };
}

void ChankManager::loadChunk(ChankID id)
{
    if (m_loadedChunks.count(id)) {
        return;
    }
    Chunk chunk;
    chunk.id = id;

}
