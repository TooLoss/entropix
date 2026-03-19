#pragma once
#include "core/GameState.hpp"

class Game {
private:
    std::unique_ptr<GameState> game_state;
    SDL_Renderer* renderer;
    SDL_Window* window;

public:
    Game(SDL_Renderer* renderer, SDL_Window* window);

    void render();
    void update();
    void init();

    void set_game_state(std::unique_ptr<GameState> game_state);
};
