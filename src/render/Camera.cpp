#include <SDL3/SDL_log.h>
#include "render/Camera.hpp"

Camera::Camera(World& world, SDL_Window* window, SDL_Renderer* renderer)
    :   world(world),
        window(window),
        renderer(renderer),
        center(static_cast<float>(world.get_size().x / 2.f),
               static_cast<float>(world.get_size().y / 2.f)),
        zoom(10.f)
{
    draw_canvas();
}

void Camera::draw_canvas() {

}
