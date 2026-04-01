#pragma once
#include "render/Camera.hpp"
#include "core/InputManager.hpp"

class GameUI {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    InputManager input;

public:
    GameUI(SDL_Renderer *renderer, SDL_Window *window);

    void hander_ui_inputs(SDL_Event *event, InputType type);
    
    virtual void init_ui();
    virtual void bind_inputs();
    virtual void render();
};



class GameUI_Play : public GameUI {
private:
    std::unique_ptr<Camera> camera;

public:
    virtual void init_ui() override;
    virtual void bind_inputs() override;
    virtual void render() override;
};
