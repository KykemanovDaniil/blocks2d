#include "src/worldManager/WorldManager.hpp"
#include "src/worldGenerator/default/DefaultGenerator.hpp"
#include <print>

void WorldManager::createWorld(int size) {
    DefaultGenerator generator(0);
    for (int i = -size; i < size; ++i) {
        Chunk chunk;
        chunk.setX(i);
        generator.generate(chunk, chunk.getX()); 
        
        m_activeChunks[i] = chunk;
    }
}
