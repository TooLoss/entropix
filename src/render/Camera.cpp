#include <SDL3/SDL_log.h>
#include <algorithm>
#include "render/Camera.hpp"

Camera::Camera(World& world, SDL_Window* window, SDL_Renderer* renderer) :
    world(world),
    window(window),
    renderer(renderer),
    cell_size(10),
    center(static_cast<float>(world.get_size().x / 2.f),
           static_cast<float>(world.get_size().y / 2.f)),
    camera_size(0,0)
{
    draw_canvas();
}

void Camera::draw_canvas() {
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);

    int min_axis = std::min(window_x, window_y);

    float margin_x = (window_x % cell_size) / 2.f;
    float margin_y = (window_y % cell_size) / 2.f;

    size_t count_x = window_x / cell_size;
    size_t count_y = window_y / cell_size;

    camera_size = Coord(count_x, count_y);

    for (size_t i = 0; i < count_x; i++) {
        for (size_t j = 0; j < count_y; j++) {
            float pos_x = i * cell_size;
            float pos_y = j * cell_size;
            float show_size_x = j == 0 || j == count_y ? margin_x : cell_size;
            float show_size_y = i == 0 || i == count_x ? margin_y : cell_size;
            SDL_FRect rect = { pos_x, pos_y, show_size_x, show_size_y };
            render_grid[Coord(i,j).vector_to_index(camera_size)] = rect;
        }
    }
}

Coord Camera::camera_to_world_pos(Coord pos) {
    Coord relative_center(camera_size.x / 2, camera_size.y / 2);
    return center + pos + relative_center * -1;
}

void Camera::render() {
    Coord world_size = world.get_size();
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

size_t Camera::get_cell_size() {
    return cell_size;
}
