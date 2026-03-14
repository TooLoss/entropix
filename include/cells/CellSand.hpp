#pragma once
#include "cells/CellAbstractFall.hpp"

class CellSand : public Cell, CellAbstractFall {
public:
    CellSand() : Cell({ 247, 179, 20, 255 }) {};

    virtual void update(Coord pos, World& world) const override;
};
