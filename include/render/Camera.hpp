#pragma once
#include "core/World.hpp"
#include "render/Canva.hpp"

class Camera : public Canva {
private:
    /** World grid. */
    World world;
    /** Render grid contains FRects, will be colored. */
    std::vector<SDL_FRect> render_grid;
    /** Size of FRect inside render_grid. */
    size_t cell_size;
    SDL_Renderer* renderer;

    /** Numbers of x and y FRect. */
    Coord grid_dim;
    /** Margin of non-squared FRect. */
    Coord margins;

    /** Init the render_grid canvas, margins and size. */
    void draw_canvas();

public:
    Camera(SDL_Renderer* renderer, Coord c_pos, Coord c_size);

    /** Convert camera coordinates into world (grid) coordinates.
    * @param pos Coord in camera position.
    * @return Coord in world position.
    */
    Coord camera_to_world_pos(Coord pos);

    /** Render the grid with the cell data contained in world. */
    void render();

    /** Zoom function. Operation will redraw canvas.
    * @param grow int unit in wich the cell_size grow.
    * @param mouse_pos Vector2<float> screen mouse position (x,y).
    */
    void zoom(int grow, Vector2<float> mouse_pos);

    void translate(int dx, int dy);

    /** Get the margin.
     * @return Coord margin x and y.
     */
    Coord get_margin();

    /** Get cell size.
    * @return size_t cell_size.
    */
    size_t get_cell_size();
};
