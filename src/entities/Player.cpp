#include "Player.hpp"
#include "../core/InputHandler.hpp"

Player::Player(SDL_Renderer* renderer, float x, float y) 
    : Entity(x, y), m_onGround(false) {
    // Agora a carregar a versão PNG para suportar transparência
    m_sprite = std::make_unique<Sprite>(renderer, "assets/sprites.png");
    m_sprite->setSourceRect(0, 0, 64, 64); // O Rick é o primeiro sprite (64x64)
}

void Player::update(float deltaTime) {
    m_velX = 0;

    // Movimento Horizontal
    if (InputHandler::getInstance().isKeyDown(SDLK_LEFT)) {
        m_velX = -MOVE_SPEED;
    } else if (InputHandler::getInstance().isKeyDown(SDLK_RIGHT)) {
        m_velX = MOVE_SPEED;
    }

    // Salto básico
    if (InputHandler::getInstance().isKeyDown(SDLK_UP) && m_onGround) {
        m_velY = JUMP_FORCE;
        m_onGround = false;
    }

    // Gravidade simples
    m_velY += GRAVITY * deltaTime;

    // Aplicar movimento
    m_x += m_velX * deltaTime;
    m_y += m_velY * deltaTime;

    // Chão temporário (limite inferior do ecrã)
    if (m_y > 450.0f) {
        m_y = 450.0f;
        m_velY = 0;
        m_onGround = true;
    }
}

void Player::render() {
    // Desenhamos o Rick com o tamanho fixo de 64x64px
    m_sprite->draw(m_x, m_y, 64.0f, 64.0f);
}