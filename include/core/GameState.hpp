#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include "core/World.hpp"
#include "core/InputManager.hpp"
#include "render/GameUI.hpp"
#include "render/Camera.hpp"
#include "render/CellSelection.hpp"

struct WindowInfo {
    int w, h;
};

class GameState {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    std::unique_ptr<GameUI> ui;
    WindowInfo info;

    void click_canvas(SDL_Event* event);

public:
    GameState(SDL_Renderer *renderer, SDL_Window *window);

    virtual ~GameState();

    virtual void render();
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void input(SDL_Event* event) = 0;

    SDL_Renderer* get_renderer();
    SDL_Window* get_window();
    GameUI* get_gameui();
    Coord get_screen_size();
};



class GameState_Play : public GameState {
private:
    bool paused{false};
    InputManager input_manager;
    World world;
    CellID cell_selected;

    // UI

    Camera camera;
    CellSelection cell_selection;

    void bind_input_manager();
    void input_place(SDL_Event* event, CellID id, bool force = false);

    // Events
    
    SDL_Event last_event;
    void toogle_pause();

public:
    GameState_Play(SDL_Renderer *renderer, SDL_Window *window);

    virtual void init() override;
    virtual void update() override;
    virtual void input(SDL_Event* event) override;
};
