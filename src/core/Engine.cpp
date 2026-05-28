#include "Engine.hpp"
#include <iostream>

bool Engine::init(const char* title, int width, int height) {
    // No SDL3, SDL_Init devolve true em caso de sucesso
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!m_windowManager.init(title, width, height)) {
        std::cerr << "Erro ao inicializar WindowManager." << std::endl;
        return false;
    }

    m_running = true;
    std::cout << "Engine inicializada com sucesso (SDL3)." << std::endl;
    return true;
}

void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_running = false;
        }
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_ESCAPE) {
                m_running = false;
            }
        }
    }
}

void Engine::update() {
    // Aqui entrará a lógica de DeltaTime e física
}

void Engine::render() {
    SDL_Renderer* renderer = m_windowManager.getRenderer();
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // Fundo quase preto
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    m_windowManager.clean();
    SDL_Quit();
    std::cout << "Engine encerrada." << std::endl;
}