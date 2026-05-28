#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <SDL3/SDL.h>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    bool init(const char* title, int width, int height);
    void clean();

    SDL_Window* getWindow() const { return m_window; }
    SDL_Renderer* getRenderer() const { return m_renderer; }

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
};

#endif