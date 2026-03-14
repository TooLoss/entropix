#include "cells/CellSand.hpp"

void CellSand::update(Coord pos, World& world) const {
    fall(pos, world);
}
