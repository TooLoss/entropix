#pragma once
#include <vector>
#include <span>
#include "utils/Coord.hpp"
#include "core/CellRegistry.hpp"

struct Pixel {
    CellID id = CellID::VOID;
    bool lock_flipflop = false;
};

class World {
public:
    Pixel VOID_PIXEL = {};

private:
    Coord size;
    std::vector<Pixel> grid;
    CellRegistry registry;
    static inline constexpr uint8_t FRAME_BUFFER{12};

    bool locker_flipflop{false};

    void update_position(Coord pos);

public:
    World(Coord size);

    /** Refresh all pixels in the grid. */
    void refresh();

    /** Set pixel at coordinate pos.
    * @param pos Coord.
    * @param pixel Pixel.
    */
    void set_pixel(Coord pos, Pixel pixel);

    /** Get pixel at coordinate pos.
    * @param pos Coord.
    * @return Pixel value at pos.
    */
    Pixel get_pixel(Coord pos) const;

    /** Check if the grid is empty at position pos.
    * @param pos Coord.
    * @return true if the grid position is empty.
    */
    bool is_empty(Coord pos);

    /** Check if a position is out of range (not in the grid).
     * @param pos Coord.
     * @return true if the pos is out of the grid.
     */
    bool is_out_of_range(Coord pos) const;

    /** Get registry reference used to store behavior of cells by id.
    * @return CellRegistry& reference to World Cell Regsitry.
    */
    CellRegistry& get_registry();

    /** Get a reference to the grid.
    * @return std::span<Pixel> grid.
    */
    std::span<Pixel> get_grid();

    /** Get the size of the grid.
    * @return Coord size of the grid.
    */
    Coord get_size() const;

    /** Swap two pixels.
    * @param in Coord.
    * @param out Coord.
    */
    void swap(Coord in, Coord out, bool lock_out = false);

    void lock(Coord pos);

    bool is_locked(Coord pos);

    Pixel create_pixel_id(CellID id) const;
};
