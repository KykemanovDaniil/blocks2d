#include "Chunk.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../blockAtlas/BlockAtlas.hpp"

void Chunk::init() {
    for (unsigned int y = 0; y < CHUNK_H; ++y) {
        for (unsigned int x = 0; x < CHUNK_W; ++x) {
            unsigned int index = x + (y * CHUNK_W);

            int globalBlockX = static_cast<int>(x) + Chunk::x * static_cast<int>(CHUNK_W);

            if (y > 50) {
                Chunk::blocks[index] = BlockType::Limestone;
            } else {
                Chunk::blocks[index] = BlockType::Air;
            }
        }
    }
}

void Chunk::draw(sf::RenderWindow& window, const sf::Texture& atlas) {
    window.draw(Chunk::mesh, &atlas);
}

void Chunk::updateMesh() {
    Chunk::mesh.setPrimitiveType(sf::PrimitiveType::Triangles);

    int solidBlock = 0;

    unsigned int currentVertex = 0;

    for (unsigned int y = 0; y < CHUNK_H; ++y) {
        for (unsigned int x = 0; x < CHUNK_W; ++x) {
            if (Chunk::blocks[x + (y * CHUNK_W)] != BlockType::Air) {
                solidBlock += 1;
            }
        }
    }

    Chunk::mesh.resize(solidBlock * 6);

    float textureSize = 18.0f;

    for (unsigned int y = 0; y < CHUNK_H; ++y) {
        for (unsigned int x = 0; x < CHUNK_W; ++x) {
            unsigned int blockIndex = x + (y * CHUNK_W);

            if (Chunk::blocks[blockIndex] != BlockType::Air) { 
                float screenX = static_cast<float>(static_cast<int>(x) + Chunk::x * static_cast<int>(CHUNK_W)) * BLOCK_SIZE;
                float screenY = static_cast<float>(y) * BLOCK_SIZE;

                if (Chunk::blocks[blockIndex] == BlockType::Limestone) {
                    Chunk::mesh[currentVertex + 0].position = sf::Vector2f(screenX, screenY);
                    Chunk::mesh[currentVertex + 0].texCoords = sf::Vector2f(0.0f, 0.0f);

                    Chunk::mesh[currentVertex + 1].position = sf::Vector2f(screenX + BLOCK_SIZE, screenY);
                    Chunk::mesh[currentVertex + 1].texCoords = sf::Vector2f(textureSize, 0.0f);

                    Chunk::mesh[currentVertex + 2].position = sf::Vector2f(screenX , screenY + BLOCK_SIZE);
                    Chunk::mesh[currentVertex + 2].texCoords = sf::Vector2f(0.0f, textureSize);

                    

                    Chunk::mesh[currentVertex + 3].position = sf::Vector2f(screenX + BLOCK_SIZE, screenY);
                    Chunk::mesh[currentVertex + 3].texCoords = sf::Vector2f(textureSize, 0.0f);

                    Chunk::mesh[currentVertex + 4].position = sf::Vector2f(screenX + BLOCK_SIZE, screenY + BLOCK_SIZE);
                    Chunk::mesh[currentVertex + 4].texCoords = sf::Vector2f(textureSize, textureSize);

                    Chunk::mesh[currentVertex + 5].position = sf::Vector2f(screenX, screenY + BLOCK_SIZE);
                    Chunk::mesh[currentVertex + 5].texCoords = sf::Vector2f(0.0f, textureSize);
                    
                    currentVertex += 6;
                }
            }
        }
    }
}