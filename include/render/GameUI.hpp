#pragma once
#include "render/Camera.hpp"
#include "core/InputManager.hpp"

class GameUI {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    InputManager input;
    static constexpr size_t CANVAS_COUNT = 0;
    std::array<std::unique_ptr<Canva>, CANVAS_COUNT> canvas;

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
    static constexpr size_t CANVAS_COUNT = 3;

public:
    virtual void init_ui() override;
    virtual void bind_inputs() override;
    virtual void render() override;
};
