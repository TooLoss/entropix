#pragma once
#include "cells/Cell.hpp"

class BehaviorLiquid {
public:
    bool fall(Coord pos, World& world) const;

    bool liquid(Coord pos, World& world) const;
};
