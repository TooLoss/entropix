#include "cells/CellWater.hpp"

void CellWater::update(Coord &pos, World &world) const {
    liquid(pos, world);
}
