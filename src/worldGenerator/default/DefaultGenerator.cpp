#include "src/worldGenerator/default/DefaultGenerator.hpp"
#include "src/worldManager/TileType/TileType.hpp" 
#include <cmath>

DefaultGenerator::DefaultGenerator(int seed) {
    m_landscapeNoise.SetSeed(seed);
    m_landscapeNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_landscapeNoise.SetFrequency(0.007f);

    m_cavesNoise.SetSeed(seed + 1); 
    m_cavesNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    m_cavesNoise.SetFrequency(0.019f);
}

void DefaultGenerator::generate(Chunk& chunk, int chunkX) {
    generateLandscape(chunk, chunkX);
    generateVegetation(chunk, chunkX);
    generateCaves(chunk, chunkX);

    chunk.updateGeometry();
}

void DefaultGenerator::generateLandscape(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        const int globalX = chunkX * static_cast<int>(CHUNK_W) + static_cast<int>(x);
        const unsigned int surfaceY = calculateSurfaceY(globalX);
        
        for (unsigned int y = 0; y < CHUNK_H; ++y) {
            
            if (y >= CHUNK_H - 3) {
                chunk.setLocalBlock(x, y, BlockType::Basalt);
                chunk.setLocalWall(x, y, WallType::Basalt);
            }
            else if (y >= CHUNK_H - 29) {
                chunk.setLocalBlock(x, y, BlockType::Andesite);
                chunk.setLocalWall(x, y, WallType::Andesite);
            }
            else if (y < surfaceY) {
                chunk.setLocalBlock(x, y, BlockType::Air);
                chunk.setLocalWall(x, y, WallType::None);
            }
            else if (y > surfaceY && y <= surfaceY + 7) {
                chunk.setLocalBlock(x, y, BlockType::Grus);
                chunk.setLocalWall(x, y, WallType::Grus);
            }
            else if (y > surfaceY && y <= surfaceY + 9) {
                chunk.setLocalBlock(x, y, BlockType::Gravel);
                chunk.setLocalWall(x, y, WallType::Gravel);
            }
            else {
                chunk.setLocalBlock(x, y, BlockType::Limestone);    
                chunk.setLocalWall(x, y, WallType::Limestone);          
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
                chunk.setLocalWall(x, y, WallType::Grass);
            }
            else if (y > surfaceY && y < surfaceY + 5) {
                chunk.setLocalBlock(x, y, BlockType::Loam);
                chunk.setLocalWall(x, y, WallType::Loam);
            }
        }
    }
}

void DefaultGenerator::generateCaves(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        const int globalX = chunkX * static_cast<int>(CHUNK_W) + static_cast<int>(x);
        
        for (unsigned int y = 0; y < CHUNK_H; ++y) {
            if (y >= CHUNK_H - 3) {
                continue;
            }

            const float caveNoiseValue = calculateCaveValue(globalX, static_cast<int>(y));

            if (std::abs(caveNoiseValue) < 0.06f) {
                chunk.setLocalBlock(x, y, BlockType::Air);
            }
        }
    }
}