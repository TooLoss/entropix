#pragma once
#include <SDL3/SDL_render.h>
#include "core/InputManager.hpp"
#include "render/Camera.hpp"

class GameState;

class GameUI {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    InputManager input;
    GameState& gamestate;

public:
    GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState &gamestate);

    void hander_ui_inputs(SDL_Event *event, InputType type);
    
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
