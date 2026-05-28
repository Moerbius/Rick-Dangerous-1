#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SDL3/SDL.h>
#include <unordered_map>

class InputHandler {
public:
    static InputHandler& getInstance() {
        static InputHandler instance;
        return instance;
    }

    void update(SDL_Event& event);
    bool isKeyDown(SDL_Keycode key) const;

private:
    InputHandler() = default;
    std::unordered_map<SDL_Keycode, bool> m_keyStates;
};

#endif