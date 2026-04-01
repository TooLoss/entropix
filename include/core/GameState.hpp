#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include "core/World.hpp"
#include "core/InputManager.hpp"
#include "render/GameUI.hpp"

class GameState {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;
    GameUI ui;

public:
    GameState(SDL_Renderer *renderer, SDL_Window *window)
    : renderer(renderer), window(window), ui(renderer, window) {};

    virtual ~GameState();

    virtual void render();
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void input(SDL_Event* event) = 0;
};



class GameState_Play : public GameState {
private:
    bool paused{false};
    InputManager input_manager;
    World world;

    void bind_input_manager();
    void input_place(SDL_Event* event, CellID id, bool force = false);

    // Events
    
    void toogle_pause();

public:
    GameState_Play(SDL_Renderer *renderer, SDL_Window *window);

    virtual void init() override;
    virtual void update() override;
    virtual void render() override;
    virtual void input(SDL_Event* event) override;
};
