#include "core/CellRegistry.hpp"

CellRegistry::CellRegistry() {
    std::fill(cell_list.begin(), cell_list.end(), nullptr);
    register_cell<CellVoid>(CellID::VOID);
    register_cell<CellSand>(CellID::SAND);
}

const Cell& CellRegistry::get(uint8_t id) const {
    if(id > this->MAX_ELEMENTS || id < 0) {
        throw std::out_of_range("Cell ID out of range.");
    }
    Cell& return_cell = *cell_list.at(id);
    return return_cell;
}

const Cell& CellRegistry::get(CellID cell_id) const {
    uint8_t id = static_cast<uint8_t>(cell_id);
    const Cell& cell = this->get(id);
    return cell;
}
