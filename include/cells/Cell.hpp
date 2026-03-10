#pragma once
#include <cstdint>
#include "utils/Coord.hpp"

class World;

enum class Mobility : uint8_t {
    STATIC,     // Will not move no matter what
    MOVABLE,    // Will not move except if pushed
    DYNAMIC     // Will move each frame
};

class Cell {
private:
    Mobility mobility = Mobility::STATIC;

public:
    virtual void update(Coord pos, World& world) const;

    void move_to(Coord in, Coord out, World& world) const;
};
