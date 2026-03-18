#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/World.hpp"
#include "render/SdlGridRenderer.hpp"

int main(int argc, char *argv[]) {
    const Coord SIZE = {600, 600};

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("SDL3 Window", 800, 600, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return 1;
    }

    std::unique_ptr<World> world = std::make_unique<World>(SIZE);
    std::unique_ptr<SdlGridRenderer> grid_renderer = std::make_unique<SdlGridRenderer>(*world, renderer, window);
    Pixel sand = world->create_pixel_id(CellID::SAND);
    world->set_pixel({1, 1}, sand);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        grid_renderer->refresh_window();

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
