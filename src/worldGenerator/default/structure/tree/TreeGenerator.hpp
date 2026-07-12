#pragma once
#include "src/worldManager/chunk/Chunk.hpp"
#include "src/worldManager/TileType/TileType.hpp"

void generateTree(Chunk& chunk, unsigned int x, unsigned int surfaceY) {
    unsigned int treeHeight = 4 + (std::rand() % 10);

    for (unsigned int i = 1; i <= treeHeight; ++i) {
        int wallY = static_cast<int>(surfaceY) - i;
            
        if (wallY >= 0) {
            chunk.setLocalWall(x, static_cast<unsigned int>(wallY), WallType::Oak);
        }
    }

    int topY = static_cast<int>(surfaceY) - treeHeight;
        
    for (int leafY = topY - 4; leafY <= topY; ++leafY) {
        for (int leafX = static_cast<int>(x) - 2; leafX <= static_cast<int>(x) + 2; ++leafX) {
                
            if (leafX >= 0 && leafX < static_cast<int>(CHUNK_W) && leafY >= 0) {
                    
                if (leafX == static_cast<int>(x) && leafY > topY - 1) {
                    continue;
                }
                    
                chunk.setLocalWall(static_cast<unsigned int>(leafX), static_cast<unsigned int>(leafY), WallType::Leaves);
                
            }
        }
    }
}