#pragma once
#include "cells/Cell.hpp"

class CellSand : public Cell {
public:
    virtual void update(Coord pos, World& world) const override;
};
