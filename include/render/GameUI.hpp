#pragma once
#include <SDL3/SDL_render.h>
#include "render/Camera.hpp"

struct WindowLayout {
    std::reference_wrapper<Canva> canva;
    Coord size = Coord(0);
    Coord position = Coord(0);
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
    
    void register_canva(WindowLayout layout);
    Canva* get_canvas(Coord pos);
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
