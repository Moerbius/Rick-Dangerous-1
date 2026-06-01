#include "Player.hpp"
#include "../core/InputHandler.hpp"
#include <algorithm>

namespace {
constexpr int SPRITE_WIDTH = 64;
constexpr int SPRITE_HEIGHT = 64;
constexpr int SPRITES_PER_ROW = 8;
constexpr int RIGHT_START_FRAME = 1;
constexpr int RIGHT_END_FRAME = 5;
constexpr int LEFT_START_FRAME = 13;
constexpr int LEFT_END_FRAME = 17;
constexpr int IDLE_RIGHT_FRAME = 0;
constexpr int IDLE_LEFT_FRAME = 12;
constexpr int SHOOT_RIGHT_FRAME = 9;
constexpr int SHOOT_LEFT_FRAME = 21;
constexpr int STICK_RIGHT_FRAME = 10;
constexpr int STICK_LEFT_FRAME = 22;
constexpr int CROUCH_RIGHT_START_FRAME = 6;
constexpr int CROUCH_RIGHT_END_FRAME = 7;
constexpr int CROUCH_LEFT_START_FRAME = 18;
constexpr int CROUCH_LEFT_END_FRAME = 19;
constexpr int BULLET_RIGHT_FRAME = 32;
constexpr int BULLET_LEFT_FRAME = 33;
constexpr float BULLET_SPEED = 480.0f;
constexpr float BULLET_Y_OFFSET = 28.0f;
constexpr float BULLET_MIN_X = -128.0f;
constexpr float BULLET_MAX_X = 2048.0f;
constexpr int BOMB_INITIAL_FRAME = 34;
constexpr float BOMB_THROW_SPEED_X = 120.0f;
constexpr float BOMB_THROW_SPEED_Y = -240.0f;
constexpr float BOMB_X_OFFSET_LEFT = 10.0f;
constexpr float BOMB_X_OFFSET_RIGHT = 38.0f;
constexpr float BOMB_Y_OFFSET = 30.0f;
constexpr float BOMB_MIN_X = -128.0f;
constexpr float BOMB_MAX_X = 2048.0f;
constexpr float BOMB_MIN_Y = -128.0f;
constexpr float BOMB_MAX_Y = 1024.0f;
}

void Player::setSpriteFrame(int frameIndex) {
    const int column = frameIndex % SPRITES_PER_ROW;
    const int row = frameIndex / SPRITES_PER_ROW;
    m_sprite->setSourceRect(column * SPRITE_WIDTH, row * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT);
}

Player::Player(SDL_Renderer* renderer, float x, float y) 
    : Entity(x, y), m_renderer(renderer), m_onGround(false) {
    // Agora a carregar a versão PNG para suportar transparência
    m_sprite = std::make_unique<Sprite>(renderer, "assets/sprites.png");
    setSpriteFrame(IDLE_RIGHT_FRAME);
}

void Player::update(float deltaTime) {
    m_velX = 0;
    bool moving = false;
    int animStart = IDLE_RIGHT_FRAME;
    int animEnd = IDLE_RIGHT_FRAME;

    // Movimento Horizontal
    if (InputHandler::getInstance().isKeyDown(SDLK_LEFT)) {
        m_velX = -MOVE_SPEED;
        moving = true;
        m_facingLeft = true;
        animStart = LEFT_START_FRAME;
        animEnd = LEFT_END_FRAME;
    } else if (InputHandler::getInstance().isKeyDown(SDLK_RIGHT)) {
        m_velX = MOVE_SPEED;
        moving = true;
        m_facingLeft = false;
        animStart = RIGHT_START_FRAME;
        animEnd = RIGHT_END_FRAME;
    }

    const bool shooting = m_onGround &&
                          InputHandler::getInstance().isKeyDown(SDLK_SPACE) &&
                          InputHandler::getInstance().isKeyDown(SDLK_UP);
    const bool crouching = m_onGround && InputHandler::getInstance().isKeyDown(SDLK_DOWN);
    const bool bombing = m_onGround &&
                         InputHandler::getInstance().isKeyDown(SDLK_SPACE) &&
                         InputHandler::getInstance().isKeyDown(SDLK_DOWN);
    const bool stickAttack = m_onGround && !crouching &&
                             InputHandler::getInstance().isKeyDown(SDLK_SPACE) &&
                             (InputHandler::getInstance().isKeyDown(SDLK_LEFT) ||
                              InputHandler::getInstance().isKeyDown(SDLK_RIGHT));

    const bool hasActiveBullet = !m_bullets.empty();
    if (shooting && !m_wasShooting && !hasActiveBullet) {
        const bool shotLeft = m_facingLeft;
        const float bulletVelX = shotLeft ? -BULLET_SPEED : BULLET_SPEED;
        const float bulletX = m_x + (shotLeft ? 8.0f : 40.0f);
        const float bulletY = m_y + BULLET_Y_OFFSET;

        m_bullets.emplace_back(
            m_renderer,
            bulletX,
            bulletY,
            bulletVelX,
            shotLeft ? BULLET_LEFT_FRAME : BULLET_RIGHT_FRAME,
            "assets/sprites.png");
    }
    m_wasShooting = shooting;

    if (bombing && !m_wasBombing) {
        const bool throwLeft = m_facingLeft;
        const float bombVelX = throwLeft ? -BOMB_THROW_SPEED_X : BOMB_THROW_SPEED_X;
        const float bombX = m_x + (throwLeft ? BOMB_X_OFFSET_LEFT : BOMB_X_OFFSET_RIGHT);
        const float bombY = m_y + BOMB_Y_OFFSET;

        m_bombs.emplace_back(
            m_renderer,
            bombX,
            bombY,
            bombVelX,
            BOMB_THROW_SPEED_Y,
            BOMB_INITIAL_FRAME,
            "assets/sprites.png");
    }
    m_wasBombing = bombing;

    if (stickAttack) {
        m_velX = 0.0f;
        m_animationTimer = 0.0f;
        m_currentFrame = m_facingLeft ? STICK_LEFT_FRAME : STICK_RIGHT_FRAME;
        setSpriteFrame(m_currentFrame);
    } else if (crouching) {
        const int crouchStart = m_facingLeft ? CROUCH_LEFT_START_FRAME : CROUCH_RIGHT_START_FRAME;
        const int crouchEnd = m_facingLeft ? CROUCH_LEFT_END_FRAME : CROUCH_RIGHT_END_FRAME;

        if (moving) {
            m_velX = m_facingLeft ? -MOVE_SPEED : MOVE_SPEED;

            if (m_currentFrame < crouchStart || m_currentFrame > crouchEnd) {
                m_currentFrame = crouchStart;
                m_animationTimer = 0.0f;
                setSpriteFrame(m_currentFrame);
            }

            m_animationTimer += deltaTime;
            if (m_animationTimer >= WALK_ANIMATION_FRAME_TIME) {
                m_animationTimer -= WALK_ANIMATION_FRAME_TIME;
                m_currentFrame++;
                if (m_currentFrame > crouchEnd) {
                    m_currentFrame = crouchStart;
                }
                setSpriteFrame(m_currentFrame);
            }
        } else {
            m_velX = 0.0f;
            m_animationTimer = 0.0f;
            m_currentFrame = crouchStart;
            setSpriteFrame(m_currentFrame);
        }
    } else if (shooting) {
        m_animationTimer = 0.0f;
        m_currentFrame = m_facingLeft ? SHOOT_LEFT_FRAME : SHOOT_RIGHT_FRAME;
        setSpriteFrame(m_currentFrame);
    } else if (moving) {
        if (m_currentFrame < animStart || m_currentFrame > animEnd) {
            m_currentFrame = animStart;
            m_animationTimer = 0.0f;
            setSpriteFrame(m_currentFrame);
        }

        m_animationTimer += deltaTime;
        if (m_animationTimer >= WALK_ANIMATION_FRAME_TIME) {
            m_animationTimer -= WALK_ANIMATION_FRAME_TIME;
            m_currentFrame++;
            if (m_currentFrame > animEnd) {
                m_currentFrame = animStart;
            }
            setSpriteFrame(m_currentFrame);
        }
    } else {
        m_animationTimer = 0.0f;
        m_currentFrame = m_facingLeft ? IDLE_LEFT_FRAME : IDLE_RIGHT_FRAME;
        setSpriteFrame(m_currentFrame);
    }

    // Salto básico
    if (!shooting && !stickAttack && !crouching && InputHandler::getInstance().isKeyDown(SDLK_UP) && m_onGround) {
        m_velY = JUMP_FORCE;
        m_onGround = false;
    }

    // Gravidade simples
    m_velY += GRAVITY * deltaTime;

    // Aplicar movimento
    m_x += m_velX * deltaTime;
    m_y += m_velY * deltaTime;

    for (Bullet& bullet : m_bullets) {
        bullet.update(deltaTime);
    }

    for (Bomb& bomb : m_bombs) {
        bomb.update(deltaTime);
    }

    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(), [](const Bullet& bullet) {
            return bullet.isOutOfBounds(BULLET_MIN_X, BULLET_MAX_X);
        }),
        m_bullets.end());

    m_bombs.erase(
        std::remove_if(m_bombs.begin(), m_bombs.end(), [](const Bomb& bomb) {
            return bomb.isExpired() || bomb.isOutOfBounds(BOMB_MIN_X, BOMB_MAX_X, BOMB_MIN_Y, BOMB_MAX_Y);
        }),
        m_bombs.end());

    // Chão temporário (limite inferior do ecrã)
    if (m_y > 450.0f) {
        m_y = 450.0f;
        m_velY = 0;
        m_onGround = true;
    }
}

void Player::render() {
    // Desenhamos o Rick com o tamanho fixo de 64x64px
    m_sprite->draw(m_x, m_y, static_cast<float>(SPRITE_WIDTH), static_cast<float>(SPRITE_HEIGHT));

    for (Bomb& bomb : m_bombs) {
        bomb.render();
    }

    for (Bullet& bullet : m_bullets) {
        bullet.render();
    }
}