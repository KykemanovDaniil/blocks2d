#include "World.hpp"
#include <cmath>

float World::getSurfaceY(const std::vector<Chunk>& chunks, float pX) {
    int globalBlockX = static_cast<int>(std::floor(pX / static_cast<float>(BLOCK_SIZE)));

    int chunkX = static_cast<int>(std::floor(static_cast<float>(globalBlockX) / static_cast<float>(CHUNK_W)));
    int localBlockX = globalBlockX % static_cast<int>(CHUNK_W);
    if (localBlockX < 0) {
        localBlockX += static_cast<int>(CHUNK_W);
    }

    for (const auto& chunk : chunks) {
        if (chunk.x == chunkX) {
            for (unsigned int y = 0; y < CHUNK_H; ++y) {
                unsigned int index = static_cast<unsigned int>(localBlockX) + (y * CHUNK_W);
                if (chunk.blocks[index] != BlockType::Air) {
                    return static_cast<float>(y * BLOCK_SIZE);
                }
            }
            break;
        }
    }
    return 0.0f; 
}