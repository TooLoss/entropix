#pragma once
#include <SDL3/SDL_render.h>
#include <functional>
#include "render/Camera.hpp"

struct WindowLayout {

    WindowLayout(std::reference_wrapper<Canva> canva, int z_index = 0)
        : canva(canva), z_index(z_index) {}

    std::reference_wrapper<Canva> canva;
    int z_index = 0;
};

class GameState;

class GameUI {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    GameState& gamestate; // TODO not useful for now
    std::vector<WindowLayout> layouts;

public:
    GameUI(SDL_Renderer *renderer, SDL_Window *window, GameState &gamestate);
    
    void register_canva(WindowLayout new_layout);
    void register_canva(WindowLayout new_layout, Coord size, Coord pos);
    Canva* get_canvas(Coord hit);
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
};
