#pragma once
#include <vector>
#include <span>
#include "utils/Coord<int>.hpp"
#include "core/CellRegistry.hpp"

struct Pixel {
    CellID id = CellID::VOID;
    bool lock_flipflop = false;
};

class World {
public:
    Pixel VOID_PIXEL = {};

private:
    Coord<int> size;
    std::vector<Pixel> grid;
    CellRegistry registry;
    static inline constexpr uint8_t FRAME_BUFFER{12};

    bool locker_flipflop{false};

    void update_position(Coord<int> pos);

public:
    World(Coord<int> size);

    /** Refresh all pixels in the grid. */
    void refresh();

    /** Set pixel at coordinate pos.
    * @param pos Coord<int>.
    * @param pixel Pixel.
    */
    void set_pixel(Coord<int> pos, Pixel pixel);

    /** Get pixel at coordinate pos.
    * @param pos Coord<int>.
    * @return Pixel value at pos.
    */
    Pixel get_pixel(Coord<int> pos) const;

    /** Check if the grid is empty at position pos.
    * @param pos Coord<int>.
    * @return true if the grid position is empty.
    */
    bool is_empty(Coord<int> pos);

    /** Check if a position is out of range (not in the grid).
     * @param pos Coord<int>.
     * @return true if the pos is out of the grid.
     */
    bool is_out_of_range(Coord<int> pos) const;

    /** Get registry reference used to store behavior of cells by id.
    * @return CellRegistry& reference to World Cell Regsitry.
    */
    CellRegistry& get_registry();

    /** Get a reference to the grid.
    * @return std::span<Pixel> grid.
    */
    std::span<Pixel> get_grid();

    /** Get the size of the grid.
    * @return Coord<int> size of the grid.
    */
    Coord<int> get_size() const;

    /** Swap two pixels.
    * @param in Coord<int>.
    * @param out Coord<int>.
    */
    void swap(Coord<int> in, Coord<int> out);

    void lock(Coord<int> pos);

    bool is_locked(Coord<int> pos);

    Pixel create_pixel_id(CellID id) const;
};
