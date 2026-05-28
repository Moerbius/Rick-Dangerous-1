#include "WindowManager.hpp"
#include <iostream>

WindowManager::WindowManager() {}

WindowManager::~WindowManager() {
    clean();
}

bool WindowManager::init(const char* title, int width, int height) {
    m_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        std::cerr << "Erro ao criar janela SDL3: " << SDL_GetError() << std::endl;
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        std::cerr << "Erro ao criar renderer SDL3: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void WindowManager::clean() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}