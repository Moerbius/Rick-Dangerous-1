#include "Sprite.hpp"
#include "../utils/ResourceManager.hpp"
#include <iostream>

Sprite::Sprite(SDL_Renderer* renderer, const std::string& filePath) 
    : m_renderer(renderer), m_hasSrcRect(false) {
    
    m_texture = ResourceManager::getInstance().loadTexture(renderer, filePath);
    
    if (m_texture) {
        // No SDL3, as propriedades da textura são obtidas de forma diferente
        SDL_GetTextureSize(m_texture, &m_texWidth, &m_texHeight);
    }
}

void Sprite::setSourceRect(int x, int y, int w, int h) {
    m_srcRect = { (float)x, (float)y, (float)w, (float)h };
    m_hasSrcRect = true;
}

void Sprite::draw(float x, float y, float width, float height) {
    if (!m_texture) return;

    SDL_FRect destRect = { 
        x, 
        y, 
        (width > 0) ? width : (float)m_texWidth, 
        (height > 0) ? height : (float)m_texHeight 
    };

    if (m_hasSrcRect) {
        // SDL3 usa SDL_RenderTexture em vez de SDL_RenderCopy
        SDL_RenderTexture(m_renderer, m_texture, &m_srcRect, &destRect);
    } else {
        SDL_RenderTexture(m_renderer, m_texture, nullptr, &destRect);
    }
}