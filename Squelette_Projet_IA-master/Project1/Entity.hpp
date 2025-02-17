#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f pos;
    int health;

    Entity(float x, float y, sf::Color color, int hp);
    virtual void update(float deltaTime, Grid& grid, std::vector<Entity*> neededEntities) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    bool isAlive() const;
    void takeDamage(int damage);
};

#endif // ENTITY_HPP