#include <SDL3/SDL_log.h>
#include "core/InputManager.hpp"

InputManager::InputManager() {
    keyboard_input.fill(SDL_EVENT_FIRST);
}

void InputManager::handle_keyboard_event(const SDL_Event& event) {
    for (size_t i = 0; i < ACTION_COUNT; i++) {
        ActionID action = static_cast<ActionID>(i);
        if (keyboard_input[i] == event.key.key)
            execute(action);
    }
}

void InputManager::bind(size_t key, ActionID id, InputType type, Command func) {
    if (type == InputType::Keyboard) {
        SDL_Keycode key_enum = static_cast<SDL_Keycode>(key);
        size_t id_pos = static_cast<size_t>(id);
        keyboard_input[id_pos] = key_enum;
        actions[id_pos] = func;
    }
}

void InputManager::handle_event(const SDL_Event& event, InputType type) {
    switch (type) {
        case InputType::Keyboard:
            handle_keyboard_event(event);
            break;
        case InputType::MouseButton:
            break;
        case InputType::MouseWheel:
            break;
    }
}

void InputManager::execute(ActionID id) {
    size_t index = static_cast<size_t>(id);
    if (actions[index])
        actions[index]();
}
