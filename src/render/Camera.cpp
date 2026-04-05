#include "render/Camera.hpp"
#include <SDL3/SDL_log.h>
#include "render/SmartGrid.hpp"

Camera::Camera(World& world, SDL_Renderer* renderer) :
    Camera(world, renderer, Coord(0), Coord(0))
{
   draw_grid();
}

Camera::Camera(World& world, SDL_Renderer* renderer, Coord c_pos, Coord c_size) :
    Canva(c_pos, c_size),
    world(world),
    renderer(renderer),
    cell_size(99) {}

void Camera::draw_grid() {
    Coord canvas_size = get_size();
    Coord canvas_origin = get_position();

    SmartGrid::SmartGrid sg = { cell_size, cell_size, canvas_size.x, canvas_size.y };
    grid_dim = sg.get_dim();
    render_grid.resize(grid_dim.x * grid_dim.y);
    std::vector<SmartGrid::Cell> cells = sg.get_cells();

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

Coord Camera::screen_to_world_tile(Coord screen_pos) {
    int lx = (screen_pos.x - get_position().x) / (int)cell_size;
    int ly = (screen_pos.y - get_position().y) / (int)cell_size;
    return Coord(world_pos_offset.x + lx, world_pos_offset.y + ly);
}

void Camera::render() {
    for (int i = 0; i < grid_dim.x; i++) {
        for (int j = 0; j < grid_dim.y; j++) {
            Coord world_pos(world_pos_offset.x + i, world_pos_offset.y + j);
            if (!world.is_out_of_range(world_pos)) {
                Pixel pixel = world.get_pixel(world_pos);
                const Cell& cell = world.get_registry().get(pixel.id);
                size_t render_index = Coord(i, j).vector_to_index(grid_dim);
                
                cell.render(world_pos, world, renderer, &render_grid[render_index]);
            }
        }
    }
    SDL_RenderPresent(renderer);
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
