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
    uint8_t update_each_frame = 1;

public:
    virtual ~Cell();

    virtual void update(Coord pos, World& world) const = 0;

    uint8_t get_update_frame() const;
};
