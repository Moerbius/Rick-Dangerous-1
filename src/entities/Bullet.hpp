#ifndef BULLET_HPP
#define BULLET_HPP

#include "../graphics/Sprite.hpp"
#include <memory>
#include <string>

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, float x, float y, float velX, int frameIndex, const std::string& spritePath);

    void update(float deltaTime);
    void render();
    bool isOutOfBounds(float minX, float maxX) const;

private:
    std::unique_ptr<Sprite> m_sprite;
    float m_x;
    float m_y;
    float m_velX;
    int m_frameIndex;
};

#endif
