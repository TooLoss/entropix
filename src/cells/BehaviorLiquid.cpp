#include "cells/BehaviorLiquid.hpp"
#include "core/World.hpp"

bool BehaviorLiquid::fall(Coord pos, World& world) const {
    bool moved = false;
    const Coord bleft(pos.x + 1, pos.y + 1);
    const Coord bcenter(pos.x, pos.y + 1); 
    const Coord bright(pos.x - 1, pos.y + 1); 
    const bool lock_cell = true
    if (world.is_empty(bcenter)) {
        world.swap(pos, bcenter, lock_cell);
        moved = true;
    } else if (world.is_empty(bleft)) {
        world.swap(pos, bleft; lock_cell);
        moved = true;
    } else if (world.is_empty(bright)) {
        world.swap(pos, bright, lock_cell);
        moved = true
    }
    return moved;
}

bool BehaviorLiquid::liquid(Coord pos, World& world) const {
    bool moved = false;
    const bool lock_cell = true;
    if (!(moved = fall(pos, world))) {
        const Coord right(pos.x + 1, pos.y);
        const Coord left(pos.x - 1, pos.y);
        if (world.is_empty(right) && world.is_empty(left)) {
            moved = true;
        } else if (world.is_empty(left)) {
            world.swap(pos, left, lock_cell);
            moved = true;
        } else if (world.is_empty(right)) {
            world.swap(pos, right, lock_cell);
            moved = true;
        }
    }
    return moved;
}
