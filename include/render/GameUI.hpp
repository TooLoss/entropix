#pragma once
#include <SDL3/SDL_render.h>
#include "render/Camera.hpp"

class GameState;

class GameUI {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    GameState& gamestate; // TODO not useful for now

public:
    GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState &gamestate);
    
    virtual void init_ui();
    virtual void render();
};



class GameUI_Play : public GameUI {
private:
    Camera& camera;

    void init_camera();

public:
    GameUI_Play(SDL_Renderer *renderer, SDL_Window *window,
                GameState &gamestate, Camera &camera);

    virtual void init_ui() override;
    virtual void render() override;
};
