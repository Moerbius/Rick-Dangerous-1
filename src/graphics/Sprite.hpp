#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL3/SDL.h>
#include <string>

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const std::string& filePath);
    ~Sprite() = default;

    void draw(float x, float y, float width = 0, float height = 0);
    void setSourceRect(int x, int y, int w, int h);

private:
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    SDL_FRect m_srcRect;
    float m_texWidth;
    float m_texHeight;
    bool m_hasSrcRect;
};

#endif