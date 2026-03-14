#pragma once
#include "cells/Cell.hpp"

class CellVoid : public Cell {
public:
    CellVoid() : Cell({ 247, 179, 20, 255 }) {};

    virtual void update(Coord pos, World& world) const override;
};
