#include "render/Camera.hpp"
#include <SDL3/SDL_log.h>

Camera::Camera(World& world, SDL_Renderer* renderer) :
    Camera(world, renderer, Coord(0), Coord(0))
{
   draw_canvas();
}

Camera::Camera(World& world, SDL_Renderer* renderer, Coord c_pos, Coord c_size) :
    Canva(c_pos, c_size),
    world(world),
    renderer(renderer),
    cell_size(99),
    margins(0),
    grid_dim(0)
{}

void Camera::draw_canvas() {
    Coord window_size = get_size();
    int window_x = window_size.x;
    int window_y = window_size.y;

    float margin_x = (window_x % cell_size) / 2.f;
    float margin_y = (window_y % cell_size) / 2.f;
    margins = Coord(margin_x, margin_y);

    size_t count_x = (window_x / cell_size) + 2;
    size_t count_y = (window_y / cell_size) + 2;

    grid_dim = Coord(count_x + 2, count_y + 2);

    render_grid.resize(grid_dim.x * grid_dim.y);
    for (size_t i = 0; i < count_x; i++) {
        for (size_t j = 0; j < count_y; j++) {
            Coord pixel_pos = Coord(i-1, j-1);
            Coord canvas_pos = get_canvas_location(pixel_pos);
            float pos_x = canvas_pos.x * cell_size + margin_x;
            float pos_y = canvas_pos.y * cell_size + margin_y;
            float show_size_x = (float)cell_size;
            float show_size_y = (float)cell_size;
            if (i == 0 || i == count_x - 1) show_size_x = cell_size - margin_x;
            if (j == 0 || j == count_y - 1) show_size_y = cell_size - margin_y;
            if (i == 0) pos_x = 0;
            if (j == 0) pos_y = 0;
            SDL_FRect rect = { pos_x, pos_y, show_size_x, show_size_y };
            render_grid[Coord(i,j).vector_to_index(grid_dim)] = rect;
        }
    }
}

Coord Camera::camera_to_world_pos(Coord pos) {
    Coord origin = get_position();
    return Coord(origin.x + pos.x, origin.y + pos.y);
}

void Camera::render() {
    for (int i = 0; i < grid_dim.x; i++) {
        for (int j = 0; j < grid_dim.y; j++) {
            Coord camera_pos(i, j);
            Coord world_pos = camera_to_world_pos(camera_pos);
            if (!world.is_out_of_range(world_pos)) {
                Pixel pixel = world.get_pixel(world_pos);
                const Cell& cell = world.get_registry().get(pixel.id);
                size_t render_index = camera_pos.vector_to_index(grid_dim);
                cell.render(world_pos, world, renderer, &render_grid[render_index]);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Camera::zoom(int grow, Vector2<float> mouse_pos) {
    // Zoom
    cell_size += grow;
    if (cell_size < 5) cell_size = 5;

    // Move origin toward mouse position
    // Coord camera_origin((grid_dim.x / 2) * cell_size,
    //                     (grid_dim.y / 2) * cell_size);
    // Vector2<float> lerp_vector(mouse_pos_x - camera_origin.x,
    //                            mouse_pos_y - camera_origin.y);
    // origin = Coord(origin.x + lerp_vector.x * GameConst::ZOOM_FOCUS_FACTOR,
    //                origin.y + lerp_vector.y * GameConst::ZOOM_FOCUS_FACTOR);

    // Draw new canvas
    draw_canvas();
}

void Camera::translate(int dx, int dy) {
    Coord origin = get_size();
    set_size(Coord(origin.x + dx, origin.y + dy));
    draw_canvas();
}

Coord Camera::get_margin() {
    return Coord(cell_size) - margins;
}

size_t Camera::get_cell_size() {
    return cell_size;
}
