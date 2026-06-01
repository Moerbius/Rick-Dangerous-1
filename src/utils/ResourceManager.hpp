#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

class ResourceManager {
public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    // Carrega uma textura. Se já existir, devolve a instância em cache.
    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath);
    
    // Liberta uma textura específica
    void freeTexture(const std::string& filePath);
    
    // Limpa todos os recursos da memória
    void clear();

private:
    ResourceManager() = default;
    ~ResourceManager() = default;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, SDL_Texture*> m_textures;
};

#endif