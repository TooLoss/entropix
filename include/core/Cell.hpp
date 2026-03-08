#pragma once
#include <cstdint>

enum class CellType : uint8_t {
    EMPTY = 0,
    SAND = 1,
    WALL = 2
};

struct Cell {
    CellType type = CellType::EMPTY;
};
