#pragma once
#include "cells/Cell.hpp"

class BehaviorLiquid {
public:
    void fall(Coord pos, World& world) const;
};
