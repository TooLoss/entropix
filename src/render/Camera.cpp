#include <SDL3/SDL_log.h>
#include <algorithm>
#include "render/Camera.hpp"
#include "core/GameConst.hpp"

Camera::Camera(World& world, SDL_Window* window, SDL_Renderer* renderer) :
    world(world),
    window(window),
    renderer(renderer),
    cell_size(99),
    center(0, 0),
    camera_size(0,0)
{
    draw_canvas();
}

void Camera::draw_canvas() {
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);

    float margin_x = (window_x % cell_size) / 2.f;
    float margin_y = (window_y % cell_size) / 2.f;

    size_t count_x = (window_x / cell_size) + 2;
    size_t count_y = (window_y / cell_size) + 2;

    camera_size = Coord(count_x, count_y);

    render_grid.resize(count_x * count_y);
    for (size_t i = 0; i < count_x; i++) {
        for (size_t j = 0; j < count_y; j++) {
            float pos_x = (i * cell_size) + margin_x;
            float pos_y = (j * cell_size) + margin_y;
            float show_size_x = (float)cell_size;
            float show_size_y = (float)cell_size;
            if (pos_x + show_size_x > window_x) show_size_x = window_x - pos_x;
            if (pos_y + show_size_y > window_y) show_size_y = window_y - pos_y;
            SDL_FRect rect = { pos_x, pos_y, show_size_x, show_size_y };
            render_grid[Coord(i,j).vector_to_index(camera_size)] = rect;
        }
    }
}

Coord Camera::camera_to_world_pos(Coord pos) {
    return Coord(center.x + pos.x, center.y + pos.y);
}

void Camera::render() {
    for (int i = 0; i < camera_size.x; i++) {
        for (int j = 0; j < camera_size.y; j++) {
            Coord camera_pos(i, j);
            Coord world_pos = camera_to_world_pos(camera_pos);
            if (!world.is_out_of_range(world_pos)) {
                Pixel pixel = world.get_pixel(world_pos);
                const Cell& cell = world.get_registry().get(pixel.id);
                size_t render_index = camera_pos.vector_to_index(camera_size);
                cell.render(world_pos, world, renderer, &render_grid[render_index]);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Camera::zoom(int speed, float mouse_pos_x, float mouse_pos_y) {
    // Zoom
    cell_size += speed;

    // Move center toward mouse position
    // Coord camera_center((camera_size.x / 2) * cell_size,
    //                     (camera_size.y / 2) * cell_size);
    // Vector2<float> lerp_vector(mouse_pos_x - camera_center.x,
    //                            mouse_pos_y - camera_center.y);
    // center = Coord(center.x + lerp_vector.x * GameConst::ZOOM_FOCUS_FACTOR,
    //                center.y + lerp_vector.y * GameConst::ZOOM_FOCUS_FACTOR);

    // Draw new canvas
    draw_canvas();
}

size_t Camera::get_cell_size() {
    return cell_size;
}
