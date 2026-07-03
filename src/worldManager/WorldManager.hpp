#pragma once
#include <map>
#include "src/worldManager/chunk/Chunk.hpp"
#include <print>

class WorldManager {
public:
    void createWorld(int size);

    void loadAtlasTexture(const char* path) {
        if (!m_blockAtlas.loadFromFile(path)) {
            std::println("Failed load tex: blockAtlas");
        }
    }

    void draw(sf::RenderTarget& target) const {
        for (auto& [index, chunk] : m_activeChunks) {
            chunk.draw(target, m_blockAtlas); 
        }
    }
private:
    sf::Texture m_blockAtlas;
    std::map<int, Chunk> m_activeChunks;
};