#pragma once
#include "cells/BehaviorLiquid.hpp"

class CellWater : public Cell, BehaviorLiquid {
public:
    CellWater() : CellWater({ 78, 113, 252, 255 }) {};

    virtual void update(Coord pos, World& world) const override;
}
