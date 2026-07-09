#pragma once

#include <unordered_map>
#include "src/worldManager/chunk/Chunk.hpp"
#include "src/player/Player.hpp"
#include "src/camera/Camera.hpp"
#include <print>
#include <SFML/OpenGL.hpp>
#include "src/core/Config.hpp"
#include "src/math/isChunkVisible/IsChunkVisible.hpp"

class WorldManager {
public:
    void createWorld(int size);
    void loadAtlasTexture(const char* path);

    void draw(sf::RenderTarget& target, const Player& player, const Camera& camera) const;
private:
    sf::Texture m_blockAtlas;
    std::unordered_map<int, Chunk> m_activeChunks;
};