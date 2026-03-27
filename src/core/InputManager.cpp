#include "core/InputManager.hpp"

InputManager::InputManager() {
    keyboard_input.fill(SDL_EVENT_FIRST);
}

void InputManager::bind(size_t key, ActionID id, InputType type, Command func) {
    if (type == InputType::Keyboard) {
        SDL_EventType event = static_cast<SDL_EventType>(key);
        keyboard_input[static_cast<size_t>(id)] = event;
    }
}

void InputManager::handle_event(const SDL_Event& event) {
    for (size_t i = 0; i < ACTION_COUNT; i++) {
        ActionID action = static_cast<ActionID>(i);
        if (keyboard_input[i] == event.type)
            execute(action);
    }
}

void InputManager::execute(ActionID id) {
    size_t index = static_cast<size_t>(id);
    if (actions[index])
        actions[index]();
}
