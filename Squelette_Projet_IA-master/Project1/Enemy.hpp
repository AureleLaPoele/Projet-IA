#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Entity.hpp"

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;
    Enemy(float x, float y, int hp);
    virtual void update(float deltaTime, Grid& grid, std::vector<Entity*> players) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif // ENEMY_HPP