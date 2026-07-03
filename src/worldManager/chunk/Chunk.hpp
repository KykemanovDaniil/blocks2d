#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "src/worldManager/blockType/BlockType.hpp"

constexpr unsigned int CHUNK_W = 16;
constexpr unsigned int CHUNK_H = 256;
constexpr unsigned int CHUNK_SIZE = CHUNK_W * CHUNK_H;

constexpr unsigned int BLOCK_SIZE = 32;

class Chunk {
public:
    void init();
    void updateGeometry();

    int getX() noexcept {
        return m_x;
    }

    void setX(int x) noexcept {
        m_x = x;
    }

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


    void draw(sf::RenderTarget& target, const sf::Texture& atlas) const {
        target.draw(m_mesh, &atlas);
    }
private:
    int m_x = 0;
    BlockType blocks[CHUNK_SIZE] = {BlockType::Air};
    sf::VertexArray m_mesh;
};