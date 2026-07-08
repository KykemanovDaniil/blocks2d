#pragma once
#include <map>
#include "src/worldManager/chunk/Chunk.hpp"
#include <print>
#include <SFML/OpenGL.hpp>

class WorldManager {
public:
    void createWorld(int size);

    void loadAtlasTexture(const char* path) {
        if (!m_blockAtlas.loadFromFile(path)) {
            std::println("Failed load tex: blockAtlas");
            return;
        }
        m_blockAtlas.setSmooth(false);
        (void)m_blockAtlas.generateMipmap();
        
        sf::Texture::bind(&m_blockAtlas);
        
        GLint maxLevel = 5; 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, maxLevel);
        
        sf::Texture::bind(nullptr);
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