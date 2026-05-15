#include <cmath>
#include <SDL3/SDL_log.h>
#include "render/Camera.hpp"
#include "render/SmartGrid.hpp"

Camera::Camera() :
    Camera(Coord(0), Coord(0))
{
   draw_grid();
}

Camera::Camera(Coord c_pos, Coord c_size) :
    Canva(c_pos, c_size),
    cell_size(99) {}

void Camera::init(GameState* gamestate, World* world) {
    set_gamestate(gamestate);
    this->world = world;
}

void Camera::draw_grid() {
    Coord canvas_size = get_size();
    Coord canvas_origin = get_position();

    grid = { cell_size, cell_size, canvas_size.x, canvas_size.y };
    grid_dim = grid.get_dim();
    render_grid.resize(grid_dim.x * grid_dim.y);
    std::vector<SmartGrid::Cell> cells = grid.get_cells();

    for (auto cell : cells) {
        SDL_FRect rect = { 
            canvas_origin.x + cell.x, 
            canvas_origin.y + cell.y,
            cell.sx, 
            cell.sy
        };
        render_grid[cell.index.vector_to_index(grid_dim)] = rect;
    }
}

void Camera::refresh_canva() {
    draw_grid();
}

Vector2<int> Camera::screen_to_world_tile(Vector2<float> screen_pos) {
    auto margins = grid.get_margins();
    Coord origin = get_position();
    int px = std::floor((screen_pos.x - margins.x - origin.x) / cell_size);
    int py = std::floor((screen_pos.y - margins.y - origin.y) / cell_size);
    return Vector2<int>(world_pos_offset.x + 1 + px,
                        world_pos_offset.y + 1 + py);
}

void Camera::render() {
    if (!world) return;
    for (int i = 0; i < grid_dim.x; i++) {
        for (int j = 0; j < grid_dim.y; j++) {
            Coord world_pos(world_pos_offset.x + i, world_pos_offset.y + j);
            if (!world->is_out_of_range(world_pos)) {
                Pixel pixel = world->get_pixel(world_pos);
                const Cell& cell = world->get_registry().get(pixel.id);
                size_t render_index = Coord(i, j).vector_to_index(grid_dim);
                
                cell.render(world_pos, *world, this->get_renderer(), &render_grid[render_index]);
            }
        }
    }
}

void Camera::zoom(int grow, Vector2<float> mouse_pos) {
    cell_size += grow;
    if (cell_size < 5) cell_size = 5;
    draw_grid();
}

void Camera::translate(int dx, int dy) {
    world_pos_offset.x += dx;
    world_pos_offset.y += dy;
}

size_t Camera::get_cell_size() {
    return cell_size;
}
