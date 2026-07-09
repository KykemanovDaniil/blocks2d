#include "src/worldManager/WorldManager.hpp"
#include "src/worldGenerator/default/DefaultGenerator.hpp"
#include "src/math/random/RandomInRange.hpp"
#include <print>

void WorldManager::createWorld(int size) {
    DefaultGenerator generator(randomInRange(-999, 999));
    for (int i = -size; i < size; ++i) {
        Chunk chunk;
        chunk.setLocalX(i);
        generator.generate(chunk, chunk.getLocalX()); 
        
        m_activeChunks[i] = chunk;
    }
}

void WorldManager::loadAtlasTexture(const char* path) {
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

void WorldManager::draw(sf::RenderTarget& target, const Player& player, const Camera& camera) const {
    float halfWidth = (camera.getBaseSize().x * camera.getCurrentZoom()) / 2.0f;
    float cameraLeft = player.getPosition().x - halfWidth;
    float cameraRight = player.getPosition().x + halfWidth;

    int startChunkX = static_cast<int>(std::floor(cameraLeft / CHUNK_W_PIXELS));
    int endChunkX = static_cast<int>(std::floor(cameraRight / CHUNK_W_PIXELS));

    for (int x = startChunkX; x <= endChunkX; ++x) {
        auto it = m_activeChunks.find(x);
        
        if (it != m_activeChunks.end()) {
            if (isChunkVisible(it->second, cameraLeft, cameraRight)) {
                it->second.draw(target, m_blockAtlas);
            }
        }
    }
}