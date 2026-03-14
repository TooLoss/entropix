#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/World.hpp"
#include "render/TerminalRender.hpp"

int main(int argc, char *argv[]) {
    const Coord SIZE = {5, 5};

    std::unique_ptr<World> world = std::make_unique<World>(SIZE);
    std::unique_ptr<TerminalRender> render = std::make_unique<TerminalRender>(*world);

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

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // Dark background
        SDL_RenderClear(renderer);

        SDL_FRect rect = { 350, 250, 100, 100 };
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
