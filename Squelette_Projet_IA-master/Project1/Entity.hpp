#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    sf::Vector2f pos;

    Entity(float x, float y, sf::Color color);
    virtual void update(float deltaTime, Grid& grid) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

#endif // ENTITY_HPP