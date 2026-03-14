#pragma once
#include "cells/Cell.hpp"

class CellVoid : public Cell {
public:
    CellVoid() : Cell({ 0, 0, 0, 0 }) {};

    virtual void update(Coord pos, World& world) const override;
};
