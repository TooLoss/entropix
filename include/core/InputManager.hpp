#pragma once
#include <functional>
#include <stdint.h>
#include <SDL3/SDL_events.h>

using Command = std::function<void()>;

static constexpr size_t KEYBOARD_SIZE = SDL_SCANCODE_COUNT;
static constexpr size_t MOUSE_SIZE = 8;
static constexpr size_t TOTAL_INPUT_SIZE = KEYBOARD_SIZE + MOUSE_SIZE;

enum class InputType { Keyboard, MouseButton, MouseWheel };

// struct InputBinding {
//     InputType type;
//     int key;
//     std::string action_name;
// };

enum class ActionID : uint8_t {
    None,
    ZoomIn,
    ZoomOut,
    Place,
    Erase,
    Count 
};

static constexpr size_t ACTION_COUNT = static_cast<size_t>(ActionID::Count);



class InputManager {
private:
    std::array<Command, static_cast<size_t>(ActionID::Count)> actions;
    std::array<SDL_EventType, static_cast<size_t>(ActionID::Count)> keyboard_input;

public:
    InputManager();

    void bind(size_t key, ActionID id, InputType type, Command func);
    void rebind(size_t new_key, ActionID id, InputType type);
    void handle_event(const SDL_Event& event);
    void execute(ActionID id);
};
