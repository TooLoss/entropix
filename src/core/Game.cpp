#include "core/Game.hpp"
#include "core/GameConst.hpp"

Game::Game(SDL_Renderer *renderer, SDL_Window *window)
    : Game(GameConst::GRID_SIZE, renderer, window) {}

Game::Game(Coord size, SDL_Renderer* renderer, SDL_Window* window) : renderer(renderer), window(window) {
    this->world = std::make_shared<World>(size);
    this->grid_renderer = std::make_unique<SdlGridRenderer>(*world, renderer, window);
}

void Game::update() {
    this->world->refresh();
}
