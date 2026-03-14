#pragma once
#include "cells/Cell.hpp"

class CellAbstractFall {
public:
    void fall(Coord pos, World& world) const;
};
