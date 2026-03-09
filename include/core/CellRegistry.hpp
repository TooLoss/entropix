#pragma once
#include <memory>
#include <array>
#include "cells/Cell.hpp"
#include <stdint.h>

enum class CellID : uint8_t {
    VOID      =  0,
    CONCRETE  =  1,
};

class CellRegistry {
public:
    static constexpr size_t MAX_ELEMENTS = 256;

private:
    std::array<std::unique_ptr<Cell>, MAX_ELEMENTS> cell_list;

public:
    CellRegistry();

    template<typename T>
    void register_cell(CellID id) {
        static_assert(std::is_base_of_v<Cell, T>, "T must inherit from ElementLogic");
        uint8_t id_int = static_cast<uint8_t>(id);
        // TODO add arguments
        cell_list[id_int] = std::make_unique<T>();
    }

    const std::unique_ptr<Cell> get(uint8_t id) const;
};
