#pragma once
#include <cstdint>

enum class BlockType : uint8_t {
    Air = 0, 
    Loam, 
    Grass, 
    Grus,
    Gravel,
    Limestone,
    Andesite,
    Basalt,
};

enum class WallType : uint8_t {
    None, 
    Loam, 
    Grass, 
    Grus,
    Gravel,
    Limestone,
    Andesite,
    Basalt,
};