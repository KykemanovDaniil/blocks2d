#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "src/worldManager/TileType/TileType.hpp"

constexpr unsigned int CHUNK_W = 16;
constexpr unsigned int CHUNK_H = 256;
constexpr unsigned int CHUNK_SIZE = CHUNK_W * CHUNK_H;

constexpr unsigned int TILE_SIZE = 32;

constexpr unsigned int CHUNK_W_PIXELS = CHUNK_W * TILE_SIZE;
constexpr unsigned int CHUNK_H_PIXELS = CHUNK_H * TILE_SIZE;

class Chunk {
public:
    void updateGeometry();

    int getLocalX() noexcept {
        return m_x;
    }
    void setLocalX(int x) noexcept {
        m_x = x;
    }

    float getGlobalX() const noexcept {
        float globalX{static_cast<float>(m_x * static_cast<int>(CHUNK_W)) * TILE_SIZE};
        return globalX;
    }

    // FOR BLOCKS

    BlockType getLocalBlock(unsigned int x, unsigned int y) noexcept {
        if (x < CHUNK_W && y < CHUNK_H) {
            return blocks[x + (y * CHUNK_W)];
        }
        return BlockType::Air;
    }

    void setLocalBlock(unsigned int x, unsigned int y, BlockType type) noexcept {
        if (x < CHUNK_W && y < CHUNK_H) {
            blocks[x + (y * CHUNK_W)] = type;
        }
    }

    // FOR WALLS

    WallType getLocalWall(unsigned int x, unsigned int y) noexcept {
        if (x < CHUNK_W && y < CHUNK_H) {
            return walls[x + (y * CHUNK_W)];
        }
        return WallType::None;
    }

    void setLocalWall(unsigned int x, unsigned int y, WallType type) noexcept {
        if (x < CHUNK_W && y < CHUNK_H) {
            walls[x + (y * CHUNK_W)] = type;
        }
    }

    void draw(sf::RenderTarget& target, const sf::Texture& atlas) const {
        target.draw(m_mesh, &atlas);
    }
private:
    int m_x = 0;

    BlockType blocks[CHUNK_SIZE] = {BlockType::Air};
    WallType walls[CHUNK_SIZE] = {WallType::None};

    sf::VertexArray m_mesh;
};