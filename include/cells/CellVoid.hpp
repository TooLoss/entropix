#pragma once
#include "cells/Cell.hpp"

class CellVoid : public Cell {
public:
    virtual Coord update(Coord current_pos) override;
};
