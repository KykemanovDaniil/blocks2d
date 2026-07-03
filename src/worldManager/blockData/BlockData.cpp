#include "BlockData.hpp"

std::array<BlockData, BLOCK_TYPES_COUNT> BlockRegistry;

void initBlockData() {
    BlockRegistry[static_cast<size_t>(BlockType::Air)] = {BlockType::Air, false, 0};

    BlockRegistry[static_cast<size_t>(BlockType::Loam)] = {BlockType::Loam, true, 0};

    BlockRegistry[static_cast<size_t>(BlockType::Grass)] = {BlockType::Grass, true, 1};

    BlockRegistry[static_cast<size_t>(BlockType::Grus)] = {BlockType::Grus, true, 2};

    BlockRegistry[static_cast<size_t>(BlockType::Gravel)] = {BlockType::Gravel, true, 3};

    BlockRegistry[static_cast<size_t>(BlockType::Limestone)] = {BlockType::Limestone, true, 4};

    BlockRegistry[static_cast<size_t>(BlockType::Andesite)] = {BlockType::Andesite, true, 5};

    BlockRegistry[static_cast<size_t>(BlockType::Basalt)] = {BlockType::Basalt, true, 6};
}
