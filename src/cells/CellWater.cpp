#include "cells/CellWater.hpp"

void CellWater::update(Coord pod, World& world) const {
    liquid(pos, world);
}
