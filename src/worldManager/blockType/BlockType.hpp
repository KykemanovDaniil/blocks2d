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
    Basalt
};