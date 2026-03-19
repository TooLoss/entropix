#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "core/Game.hpp"
#include "core/GameConst.hpp"

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

    Game game(renderer, window);

    game.set_game_state(std::make_unique<GameState_Play>(renderer, window));

    auto previous_time = SDL_GetTicks();
    Uint64 frame_time = 0;

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            game.input(&event);
        }

        auto current_time = SDL_GetTicks();
        Uint64 delta_time = current_time - previous_time;
        previous_time = current_time;

        frame_time += delta_time;

        while (frame_time >= GameConst::GAME_TICK) {
            game.update();
            frame_time -= GameConst::GAME_TICK;
        }

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);
        game.render();
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
