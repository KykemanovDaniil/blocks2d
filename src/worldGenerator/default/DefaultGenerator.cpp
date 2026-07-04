#include "src/worldGenerator/default/DefaultGenerator.hpp"
#include "src/worldManager/blockType/BlockType.hpp" 
#include <cmath>

DefaultGenerator::DefaultGenerator(int seed) {
    m_landscapeNoise.SetSeed(seed);
    m_landscapeNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_landscapeNoise.SetFrequency(0.007f);
}

void DefaultGenerator::generate(Chunk& chunk, int chunkX) {
    generateLandscape(chunk, chunkX);
    generateVegetation(chunk, chunkX);
    generateStructures(chunk, chunkX);

    chunk.updateGeometry();
}

void DefaultGenerator::generateLandscape(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        int globalX = chunkX * CHUNK_W + x;
        unsigned int surfaceY = calculateSurfaceY(globalX);
        for (unsigned int y = 0; y < CHUNK_H; ++y) {
            if (y < surfaceY) {
                chunk.setLocalBlock(x, y, BlockType::Air);
            }
            else if (y == CHUNK_H - 1) {
                chunk.setLocalBlock(x, y, BlockType::Basalt);
            } 
            else if (y > surfaceY) {
                chunk.setLocalBlock(x, y, BlockType::Limestone);              
            }  
        }
    }
}

void DefaultGenerator::generateVegetation(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        int globalX = chunkX * CHUNK_W + x;
        unsigned int surfaceY = calculateSurfaceY(globalX);
        for (unsigned int y = 0; y < CHUNK_H; ++y) {
            if (y == surfaceY) {
                chunk.setLocalBlock(x, y, BlockType::Grass);
            }
            else if (y > surfaceY && y < surfaceY + 5) {
                chunk.setLocalBlock(x, y, BlockType::Loam);
            }
        }
    }
}

void DefaultGenerator::generateStructures(Chunk& chunk, int chunkX) {
}
