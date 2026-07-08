#include "TileData.hpp"

std::array<BlockData, BLOCK_TYPES_COUNT> BlockRegistry;
std::array<WallData, WALL_TYPES_COUNT> WallRegistry;

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

void initWallData() {
    WallRegistry[static_cast<size_t>(WallType::None)] = {WallType::None, 0};

    WallRegistry[static_cast<size_t>(WallType::Loam)] = {WallType::Loam, 0};

    WallRegistry[static_cast<size_t>(WallType::Grass)] = {WallType::Grass, 1};

    WallRegistry[static_cast<size_t>(WallType::Grus)] = {WallType::Grus, 2};

    WallRegistry[static_cast<size_t>(WallType::Gravel)] = {WallType::Gravel, 3};

    WallRegistry[static_cast<size_t>(WallType::Limestone)] = {WallType::Limestone, 4};

    WallRegistry[static_cast<size_t>(WallType::Andesite)] = {WallType::Andesite, 5};

    WallRegistry[static_cast<size_t>(WallType::Basalt)] = {WallType::Basalt, 6};
}