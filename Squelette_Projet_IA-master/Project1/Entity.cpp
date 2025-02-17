#include "Entity.hpp"

Entity::Entity(float x, float y, sf::Color color, int hp) : health(hp) {
    pos.x = x;
    pos.y = y;
    shape.setSize({ 35, 35 });
    shape.setPosition(pos.x, pos.y);
    shape.setFillColor(color);
	shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
}

bool Entity::isAlive() const {
    return health > 0;
}

void Entity::takeDamage(int damage) {
    health -= damage;
}
