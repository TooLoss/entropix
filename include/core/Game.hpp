#pragma once
#include "core/World.hpp"
#include "render/SdlGridRenderer.hpp"
#include "core/GameState.hpp"

class Game {
private:
    std::shared_ptr<World> world;
    std::unique_ptr<SdlGridRenderer> grid_renderer;
    std::unique_ptr<GameState> game_state;
    SDL_Renderer* renderer;
    SDL_Window* window;

public:
    Game(SDL_Renderer* renderer, SDL_Window* window);
    Game(Coord size, SDL_Renderer* renderer, SDL_Window* window);

    void render();
    void update();
};
