#pragma once
#include <vector>
#include "utils/Coord.hpp"

namespace SmartGrid {

struct Cell {
    float x, y = 0;
    float sx, sy = 0.f;
    Coord index;
};

struct SmartGrid {

    /*  O-x/i
     *  |
     *  y/j
     */

    /** Size of Cells. */
    size_t sx = 0, sy = 0;
    /** Size of the window. */
    size_t wx = 0, wy = 0;

    std::vector<Cell> get_cells() {
        std::vector<Cell> cells;

        float margin_x = (float)(wx % sx) / 2.f;
        float margin_y = (float)(wy % sy) / 2.f;

        size_t count_x = (wx / sx) + 2;
        size_t count_y = (wy / sy) + 2;
        Coord dim(count_x, count_y);

        cells.resize(dim.x * dim.y);
        for (size_t i = 0; i < count_x; i++) {
            for (size_t j = 0; j < count_y; j++) {
                Coord p(i-1, j-1);
                float x, y;
                if (i == 0) x = 0;
                else x = margin_x + (p.x * sx);

                if (j == 0) y = 0;
                else y = margin_y + (p.y * sy);

                float cx, cy;
                if (i == 0 || i == dim.x - 1) cx = sx - margin_x;
                else cx = sx;

                if (j == 0 || j == dim.y - 1) cy = sy - margin_y;
                else cy = sy;

                const Cell cell = {x, y, cx, cy, Coord(i,j)};
                cells[Coord(i, j).vector_to_index(dim)] = cell;
            }
        }

        return cells;
    }

    Coord get_dim() {
        size_t count_x = (wx / sx) + 2;
        size_t count_y = (wy / sy) + 2;
        Coord dim(count_x, count_y);
        return dim;
    }

    size_t get_count() {
        Coord dim = get_dim();
        return dim.x * dim.y;
    }

    Vector2<float> get_margins() {
        float margin_x = (float)(wx % sx) / 2.f;
        float margin_y = (float)(wy % sy) / 2.f;
        return Vector2<float>(margin_x, margin_y);
    }
};

}
