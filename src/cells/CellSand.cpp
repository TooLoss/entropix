#include "cells/CellSand.hpp"
#include "core/World.hpp"

void CellVoid::update(Coord pos, World& world) const {
    const Coord bleft = pos + (Coord){-1, -1};
    const Coord bcenter = pos + (Coord){0, -1};
    const Coord bright = pos + (Coord){1, -1};
    if (world.is_empty(bcenter))
}
