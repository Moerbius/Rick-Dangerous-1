#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Bomb.hpp"
#include "../graphics/Sprite.hpp"
#include <memory>
#include <vector>

class Player : public Entity {
public:
    Player(SDL_Renderer* renderer, float x, float y);
    ~Player() override = default;

    void update(float deltaTime) override;
    void render() override;

private:
    SDL_Renderer* m_renderer = nullptr;
    std::unique_ptr<Sprite> m_sprite;
    std::vector<Bullet> m_bullets;
    std::vector<Bomb> m_bombs;
    bool m_onGround;
    bool m_facingLeft = false;
    bool m_wasShooting = false;
    bool m_wasBombing = false;
    float m_animationTimer = 0.0f;
    int m_currentFrame = 0;
    
    const float MOVE_SPEED = 200.0f;
    const float JUMP_FORCE = -500.0f;
    const float GRAVITY = 1200.0f;
    const float WALK_ANIMATION_FRAME_TIME = 0.10f;

    void setSpriteFrame(int frameIndex);
};

#endif