#pragma once
#include "utils/Coord.hpp"
#include "core/World.hpp"
#include <cstdint>

enum class Mobility : uint8_t {
    STATIC,     // Will not move no matter what
    MOVABLE,    // Will not move except if pushed
    DYNAMIC     // Will move each frame
};

class Cell {
private:
    Mobility mobility;
public:
    virtual void update(World& world);
};
