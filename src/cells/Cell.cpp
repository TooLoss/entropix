#include "cells/Cell.hpp"

Cell::~Cell() {}

uint8_t Cell::get_update_frame() const {
    return this->update_each_frame;
}
