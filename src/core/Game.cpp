#include "core/Game.hpp"
#include "core/GameConst.hpp"

Game::Game(SDL_Renderer *renderer, SDL_Window *window)
: Game(GameConst::GRID_SIZE, renderer, window) {}

void Game::render() {
    this->game_state->render();
}

void Game::update() {
    this->game_state->update();
}

void Game::init() {
    this->game_state->init();
}

void Game::set_game_state(std::unique_ptr<GameState> game_state) {
    this->game_state = std::move(game_state);
    this->game_state->init();
}
