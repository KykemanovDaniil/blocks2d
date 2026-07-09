#pragma once

#include <SFML/Graphics.hpp>
#include "src/worldManager/chunk/Chunk.hpp"

inline bool isChunkVisible(const Chunk& chunk, float cameraLeft, float cameraRight) noexcept {
    float chunkLeft = chunk.getGlobalX();
    float chunkRight = chunkLeft + CHUNK_W_PIXELS;

    return chunkRight >= cameraLeft && chunkLeft <= cameraRight;
}
