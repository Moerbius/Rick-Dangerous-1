#include "Engine.hpp"
#include "InputHandler.hpp"
#include "../entities/Player.hpp"
#include <iostream>
#include <SDL3_image/SDL_image.h>

Engine::Engine() = default;
Engine::~Engine() = default;

bool Engine::init(const char* title, int width, int height) {
    // No SDL3, SDL_Init devolve true em caso de sucesso
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (!m_windowManager.init(title, width, height)) {
        std::cerr << "Erro ao inicializar WindowManager." << std::endl;
        SDL_Quit();
        return false;
    }

    m_player = std::make_unique<Player>(m_windowManager.getRenderer(), 100.0f, 100.0f);
    m_lastTime = SDL_GetTicks();

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
        InputHandler::getInstance().update(event);
    }

    if (InputHandler::getInstance().isKeyDown(SDLK_ESCAPE)) {
        m_running = false;
    }
}

void Engine::update() {
    uint64_t currentTime = SDL_GetTicks();
    // DeltaTime em segundos
    float deltaTime = (currentTime - m_lastTime) / 1000.0f;
    m_lastTime = currentTime;

    if (m_player) {
        m_player->update(deltaTime);
    }
}

void Engine::render() {
    SDL_Renderer* renderer = m_windowManager.getRenderer();
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255); // Fundo quase preto
    SDL_RenderClear(renderer);

    if (m_player) {
        m_player->render();
    }

    SDL_RenderPresent(renderer);
}

void Engine::clean() {
    m_player.reset(); // Destruir o player antes do renderer/janela
    m_windowManager.clean();
    SDL_Quit();
    std::cout << "Engine encerrada." << std::endl;
}