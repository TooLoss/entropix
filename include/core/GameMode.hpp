#pragma once
#include <memory>

class GameMode {
private:
    std::unique_ptr<GameState> game_state;
    std::unique_ptr<GameUI> game_ui;
}
