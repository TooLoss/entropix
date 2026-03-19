#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include <vector>
#include "core/World.hpp"

class GameState {
protected:
    SDL_Renderer* renderer;
    SDL_Window* window;

public:
    GameState(SDL_Renderer *renderer, SDL_Window *window)
    : renderer(renderer), window(window) {};

    virtual ~GameState();

    virtual void render() = 0;
    virtual void update() = 0;
    virtual void init() = 0;
    virtual void input(SDL_Event* event) = 0;
};



class GameState_Play : public GameState {
private:
    uint8_t cell_size;
    std::vector<SDL_FRect> render_grid;
    std::shared_ptr<World> world;
    bool paused{false};

    void create_grid();
    void calculate_size();

    void input_place(SDL_Event* event, CellID id, bool force = false);

public:
    GameState_Play(SDL_Renderer *renderer, SDL_Window *window)
    : GameState(renderer, window) {}

    virtual void init() override;
    virtual void update() override;
    virtual void render() override;
    virtual void input(SDL_Event* event) override;
};
