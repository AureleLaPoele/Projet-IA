#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Color color) {
    pos.x = x;
    pos.y = y;
    shape.setSize({ 35, 35 });
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(color);
}
