#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "../graphics/Sprite.hpp"
#include <memory>

class Player : public Entity {
public:
    Player(SDL_Renderer* renderer, float x, float y);
    ~Player() override = default;

    void update(float deltaTime) override;
    void render() override;

private:
    std::unique_ptr<Sprite> m_sprite;
    bool m_onGround;
    
    const float MOVE_SPEED = 200.0f;
    const float JUMP_FORCE = -500.0f;
    const float GRAVITY = 1200.0f;
};

#endif