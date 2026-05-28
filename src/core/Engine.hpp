#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SDL3/SDL.h>
#include "WindowManager.hpp"

class Engine {
public:
    static Engine& getInstance() {
        static Engine instance;
        return instance;
    }

    bool init(const char* title, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool isRunning() const { return m_running; }
    SDL_Renderer* getRenderer() const { return m_windowManager.getRenderer(); }

private:
    Engine() = default;
    ~Engine() = default;
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    bool m_running = false;
    WindowManager m_windowManager;
};

#endif