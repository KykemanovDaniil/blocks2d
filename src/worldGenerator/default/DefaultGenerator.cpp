#include "DefaultGenerator.hpp"
#include "src/worldManager/TileType/TileType.hpp" 
#include "src/worldGenerator/default/structure/tree/TreeGenerator.hpp"
#include <cmath>
#include <print>

DefaultGenerator::DefaultGenerator(int seed) {
    m_landscapeNoise.SetSeed(seed);
    m_landscapeNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    m_landscapeNoise.SetFrequency(0.007f);

    m_cavesNoise.SetSeed(seed + 1); 
    m_cavesNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    m_cavesNoise.SetFrequency(0.019f);

    std::srand(static_cast<unsigned int>(seed));
}

void DefaultGenerator::generate(Chunk& chunk, int chunkX) {
    generateLandscape(chunk, chunkX);
    generateVegetation(chunk, chunkX);
    generateCaves(chunk, chunkX);
    generateTrees(chunk, chunkX);

    chunk.updateGeometry();
}

void DefaultGenerator::generateLandscape(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        const int globalX = chunkX * static_cast<int>(CHUNK_W) + static_cast<int>(x);
        const unsigned int surfaceY = calculateSurfaceY(globalX);
        
        for (unsigned int y = surfaceY + 1; y < CHUNK_H; ++y) {
            
            if (y >= CHUNK_H - 3) {
                chunk.setLocalBlock(x, y, BlockType::Basalt);
                chunk.setLocalWall(x, y, WallType::Basalt);
            }
            else if (y >= CHUNK_H - 29) {
                chunk.setLocalBlock(x, y, BlockType::Andesite);
                chunk.setLocalWall(x, y, WallType::Andesite);
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
        unsigned int surfaceY = calculateSurfaceY(globalX);

        for (unsigned int y = surfaceY; y < CHUNK_H - 3; ++y) {
            const float caveNoiseValue = calculateCaveValue(globalX, static_cast<int>(y));

            if (std::abs(caveNoiseValue) < 0.06f) {
                chunk.setLocalBlock(x, y, BlockType::Air);
            }
        }
    }
}

void DefaultGenerator::generateTrees(Chunk& chunk, int chunkX) {
    for (unsigned int x = 0; x < CHUNK_W; ++x) {
        int globalX = chunkX * CHUNK_W + x;
        unsigned int surfaceY = calculateSurfaceY(globalX);

        if (std::rand() % 100 > 15) {
            continue; 
        }

       if (chunk.getLocalBlock(x, surfaceY) != BlockType::Grass) {
            continue;
        }

        generateTree(chunk, x, surfaceY);

    }
}