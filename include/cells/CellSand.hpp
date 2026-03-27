#pragma once
#include "cells/BehaviorFall.hpp"

class CellSand : public Cell, BehaviorLiquid {
public:
    CellSand() : Cell({ 247, 179, 20, 255 }) {};

    virtual void update(Coord pos, World& world) const override;
};
