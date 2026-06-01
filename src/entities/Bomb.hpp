#ifndef BOMB_HPP
#define BOMB_HPP

#include "../graphics/Sprite.hpp"
#include <memory>
#include <string>

class Bomb {
public:
    Bomb(SDL_Renderer* renderer,
         float x,
         float y,
         float velX,
         float velY,
         int frameIndex,
         const std::string& spritePath,
         float fuseSeconds = 2.0f);

    void update(float deltaTime);
    void render();

    bool isExpired() const;
    bool isOutOfBounds(float minX, float maxX, float minY, float maxY) const;

private:
    std::unique_ptr<Sprite> m_sprite;
    float m_x;
    float m_y;
    float m_velX;
    float m_velY;
    int m_frameIndex;
    float m_fuseDuration;
    float m_timeToLive;
};

#endif
