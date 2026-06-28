#pragma once

#include <vector>
#include "../chunk/Chunk.hpp"

struct World {
    std::vector<Chunk> chunks;

    float getSurfaceY(float playerX);
};