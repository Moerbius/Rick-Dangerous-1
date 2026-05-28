#include "ResourceManager.hpp"
#include <SDL3_image/SDL_image.h>
#include <iostream>

SDL_Texture* ResourceManager::loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
    // Verifica se a textura já está no mapa
    auto it = m_textures.find(filePath);
    if (it != m_textures.end()) {
        return it->second;
    }

    // Utilizamos IMG_Load da SDL3_image para suportar múltiplos formatos (incluindo PNG)
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Erro ao carregar imagem: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface); // Já não precisamos da superfície

    if (!texture) {
        std::cerr << "Erro ao criar textura de " << filePath << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    m_textures[filePath] = texture;
    return texture;
}

void ResourceManager::freeTexture(const std::string& filePath) {
    auto it = m_textures.find(filePath);
    if (it != m_textures.end()) {
        SDL_DestroyTexture(it->second);
        m_textures.erase(it);
    }
}

void ResourceManager::clear() {
    for (auto& pair : m_textures) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    m_textures.clear();
}