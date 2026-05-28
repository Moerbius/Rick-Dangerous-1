#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity {
public:
    Entity(float x, float y) : m_x(x), m_y(y), m_velX(0.0f), m_velY(0.0f) {}
    virtual ~Entity() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;

    float getX() const { return m_x; }
    float getY() const { return m_y; }
    void setPosition(float x, float y) { m_x = x; m_y = y; }

protected:
    float m_x, m_y;
    float m_velX, m_velY;
};

#endif