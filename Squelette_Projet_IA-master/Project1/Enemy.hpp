#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y);
    virtual void update(float deltaTime, Grid& grid) = 0;
};

#endif // ENEMY_HPP