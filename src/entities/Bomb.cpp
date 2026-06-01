#include "Bomb.hpp"
#include <algorithm>
#include <array>

namespace {
constexpr int SPRITE_WIDTH = 64;
constexpr int SPRITE_HEIGHT = 64;
constexpr int SPRITES_PER_ROW = 8;
constexpr float BOMB_DRAW_WIDTH = 32.0f;
constexpr float BOMB_DRAW_HEIGHT = 32.0f;
constexpr float BOMB_GRAVITY = 1200.0f;
constexpr std::array<int, 10> BOMB_ANIMATION_FRAMES = {34, 33, 34, 33, 34, 35, 36, 37, 38, 39};
}

Bomb::Bomb(SDL_Renderer* renderer,
           float x,
           float y,
           float velX,
           float velY,
           int frameIndex,
           const std::string& spritePath,
           float fuseSeconds)
    : m_x(x),
      m_y(y),
      m_velX(velX),
      m_velY(velY),
            m_frameIndex(frameIndex),
            m_fuseDuration(fuseSeconds),
      m_timeToLive(fuseSeconds) {
    m_sprite = std::make_unique<Sprite>(renderer, spritePath);
        m_frameIndex = BOMB_ANIMATION_FRAMES.front();
}

void Bomb::update(float deltaTime) {
    m_velY += BOMB_GRAVITY * deltaTime;
    m_x += m_velX * deltaTime;
    m_y += m_velY * deltaTime;
    m_timeToLive -= deltaTime;

    const float elapsed = m_fuseDuration - m_timeToLive;
    const float normalized = std::clamp(elapsed / m_fuseDuration, 0.0f, 0.9999f);
    const size_t frameSlot = static_cast<size_t>(normalized * static_cast<float>(BOMB_ANIMATION_FRAMES.size()));
    m_frameIndex = BOMB_ANIMATION_FRAMES[frameSlot];
}

void Bomb::render() {
    const int column = m_frameIndex % SPRITES_PER_ROW;
    const int row = m_frameIndex / SPRITES_PER_ROW;
    m_sprite->setSourceRect(column * SPRITE_WIDTH, row * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
    m_sprite->draw(m_x, m_y, BOMB_DRAW_WIDTH, BOMB_DRAW_HEIGHT);
}

bool Bomb::isExpired() const {
    return m_timeToLive <= 0.0f;
}

bool Bomb::isOutOfBounds(float minX, float maxX, float minY, float maxY) const {
    return m_x < minX || m_x > maxX || m_y < minY || m_y > maxY;
}
