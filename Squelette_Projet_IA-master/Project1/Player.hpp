#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    std::string direction;
    sf::RectangleShape directionShape;
    static constexpr float SPEED = 200.0f;
    static constexpr int DAMAGE = 20;
    static constexpr float ATTACK_COOLDOWN = 0.5f;
    float attackTimer;

    Player(float x, float y, int hp);
    void attack(std::vector<Entity*> enemies);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> enemies) override;
    void draw(sf::RenderWindow& window) override;
};

#endif // PLAYER_HPP