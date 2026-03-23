#include "render/Camera.hpp"

Camera::Camera(World &world)
    : world(world), corner_start(0, 0), corner_end(world.get_size()) {
    refresh_rectangles();
};

void Camera::refresh_rectangles() {
    calculate_size();
    Coord size = get_camera_size();
    render_grid.resize(size.x * size.y);
    for (int i = corner_start.x; i < corner_end.x; i++) {
        for (int j = corner_start.y; j < corner_start.y; j++) {
            Coord pos(i,j);
            Coord world_pos(i*cell_size, j*cell_size);
            SDL_FRect rect = {(float)world_pos.x, (float)world_pos.y,
                              (float)cell_size, (float)cell_size};
            render_grid[pos.vector_to_index(size)] = rect;
        }
    }
}

void Camera::calculate_size() {
    Coord camera_size = get_camera_size();
    int window_x, window_y;
    SDL_GetWindowSize(this->window, &window_x, &window_y);
    int size_x = (int)(window_x/camera_size.x);
    int size_y = (int)(window_y/camera_size.y);
    cell_size = std::min(size_x, size_y);
}

Coord Camera::get_camera_size() {
    return Coord(
        corner_end.x - corner_start.x,
        corner_end.y - corner_start.y
    );
}

void Camera::zoom(int speed, Coord mouse_pos) {
    if (corner_end.x > corner_start.x && corner_end.y > corner_start.y) {
        corner_end = Coord(corner_end.x - speed, corner_end.y - speed);
        corner_start = Coord(corner_start.x + speed, corner_start.y + speed);
        refresh_rectangles();
    }
}

void Camera::render() {
    Coord size = get_camera_size();
    for (int i = 0; i < size.x; i++) {
        for (int j = 0; j < size.y; j++) {
            Coord pos(i, j);
            Pixel pixel = world.get_pixel(pos);
            const Cell& cell = world.get_registry().get(pixel.id);
            size_t index = pos.vector_to_index(size);
            cell.render(pos, world, renderer, &render_grid[index]);
        }
    }
    SDL_RenderPresent(renderer);
}

uint8_t Camera::get_cell_size() const {
    return cell_size;
}

Coord Camera::get_camera_position() const {
    return corner_start;
}
