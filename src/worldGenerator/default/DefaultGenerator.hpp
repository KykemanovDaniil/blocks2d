#pragma once 
#include "src/worldManager/chunk/Chunk.hpp" 
#include "libs/noise/FastNoiseLite.h"

class DefaultGenerator {
public:
    DefaultGenerator(int seed = 1337);

    void generate(Chunk& chunk, int chunkX);

private:
    FastNoiseLite m_landscapeNoise;

    unsigned int calculateSurfaceY(int globalX) const {
        float noiseVal = const_cast<FastNoiseLite&>(m_landscapeNoise).GetNoise(static_cast<float>(globalX), 0.0f);
        return m_baseLevel + static_cast<int>(noiseVal * 20.0f);
    }

    void generateLandscape(Chunk& chunk, int chunkX);
    void generateVegetation(Chunk& chunk, int chunkX);
    void generateStructures(Chunk& chunk, int chunkX);

    int m_seaLevel = 64;
    int m_baseLevel = 74;
};
