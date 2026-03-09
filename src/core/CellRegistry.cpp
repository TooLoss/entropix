#include "core/CellRegistry.hpp"
#include "cells/CellVoid.hpp"

CellRegistry::CellRegistry() {
    std::fill(cell_list.begin(), cell_list.end(), nullptr);
    register_cell<CellVoid>(CellID::VOID);
}
