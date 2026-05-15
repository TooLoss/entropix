#include "core/Game.hpp"

Game::Game(SDL_Renderer *renderer, SDL_Window *window)
: renderer(renderer), window(window) {}

void Game::render() {
    this->game_state->render();
}

void Game::update() {
    this->game_state->update();
}

void Game::init() {
    this->game_state->init();
}

void Game::input(SDL_Event* event) {
    this->game_state->input(event);
}

void Game::set_game_state(std::unique_ptr<GameState> game_state) {
    if (game_state != nullptr) {
        game_state->init();
        this->game_state = std::move(game_state);
    }
}
