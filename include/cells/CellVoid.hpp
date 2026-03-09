#pragma once
#include "cells/Cell.hpp"

class CellVoid : public Cell {
public:
    virtual void update(Coord pos, World& world) override;
};
