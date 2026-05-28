#include "InputHandler.hpp"

void InputHandler::update(SDL_Event& event) {
    if (event.type == SDL_EVENT_KEY_DOWN) {
        m_keyStates[event.key.key] = true;
    } else if (event.type == SDL_EVENT_KEY_UP) {
        m_keyStates[event.key.key] = false;
    }
}

bool InputHandler::isKeyDown(SDL_Keycode key) const {
    auto it = m_keyStates.find(key);
    return (it != m_keyStates.end()) ? it->second : false;
}