#pragma once
#include "cells/Cell.hpp"

class CellAbstractFall : public Cell {
public:
    virtual void update(Coord pos, World& world) const override;
};
