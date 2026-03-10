#pragma once
#include "core/World.hpp"

class TerminalRender {
private:
    World& world;

public:
    TerminalRender(World& world);

    void print() const;
};
