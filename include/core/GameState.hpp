#pragma once
#include <SDL3/SDL_render.h>

class GameState {
private:
    SDL_Renderer* renderer;
    SDL_Window* window;

public:
    GameState(SDL_Renderer* renderer, SDL_Window* window);

    virtual void render();
    virtual void input();
};

class GameState_Play : public GameState {

};
