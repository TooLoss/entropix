#pragma once
#include "core/World.hpp"
#include "render/Canva.hpp"
#include "render/SmartGrid.hpp"

class Camera : public Canva {
private:
    /** World grid. */
    World& world;
    /** Render grid contains FRects, will be colored. */
    std::vector<SDL_FRect> render_grid;
    /** Size of FRect inside render_grid. */
    size_t cell_size;

    /** Numbers of x and y FRect. */
    Coord grid_dim;
    /** World position of the camera. */
    Coord world_pos_offset;
    /** Smart grid to generate position of each cell for SDL3 */
    SmartGrid::SmartGrid grid;

    /** Init the render_grid canvas, margins and size. */
    void draw_grid();

public:
    Camera(GameState& owner, World& world, Coord c_pos, Coord c_size);
    Camera(GameState& owner, World& world);

    virtual void refresh_canva() override;

    /** Convert camera coordinates into world (grid) coordinates.
    * @param pos Coord in camera position.
    * @return Coord in world position.
    */
    Vector2<int> screen_to_world_tile(Vector2<float> screen_pos);

    /** Render the grid with the cell data contained in world. */
    virtual void render() override;

    /** Zoom function. Operation will redraw canvas.
    * @param grow int unit in wich the cell_size grow.
    * @param mouse_pos Vector2<float> screen mouse position (x,y).
    */
    void zoom(int grow, Vector2<float> mouse_pos);

    void translate(int dx, int dy);

    /** Get cell size.
    * @return size_t cell_size.
    */
    size_t get_cell_size();
};
