#include "cells/CellSand.hpp"
#include "core/World.hpp"

void CellSand::update(Coord pos, World& world) const {
    const Coord bleft(pos.x + 1, pos.y + 1);
    const Coord bcenter(pos.x, pos.y + 1); 
    const Coord bright(pos.x - 1, pos.y + 1); 
    if (world.is_empty(bcenter)) {
        world.swap(pos, bcenter);
    } else if (world.is_empty(bleft)) {
        world.swap(pos, bleft);
    } else if (world.is_empty(bright)) {
        world.swap(pos, bright);
    }
}
