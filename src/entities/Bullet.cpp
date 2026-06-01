#include "Bullet.hpp"

namespace {
constexpr int SPRITE_WIDTH = 64;
constexpr int SPRITE_HEIGHT = 64;
constexpr int SPRITES_PER_ROW = 8;
constexpr float BULLET_DRAW_WIDTH = 32.0f;
constexpr float BULLET_DRAW_HEIGHT = 32.0f;
}

Bullet::Bullet(SDL_Renderer* renderer, float x, float y, float velX, int frameIndex, const std::string& spritePath)
    : m_x(x), m_y(y), m_velX(velX), m_frameIndex(frameIndex) {
    m_sprite = std::make_unique<Sprite>(renderer, spritePath);
}

void Bullet::update(float deltaTime) {
    m_x += m_velX * deltaTime;
}

void Bullet::render() {
    const int column = m_frameIndex % SPRITES_PER_ROW;
    const int row = m_frameIndex / SPRITES_PER_ROW;
    m_sprite->setSourceRect(column * SPRITE_WIDTH, row * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
    m_sprite->draw(m_x, m_y, BULLET_DRAW_WIDTH, BULLET_DRAW_HEIGHT);
}

bool Bullet::isOutOfBounds(float minX, float maxX) const {
    return m_x < minX || m_x > maxX;
}
