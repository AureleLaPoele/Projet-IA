#include "Monster.hpp"
#include <cmath>

Monster::Monster(float x, float y, int hp) : Entity(x, y, sf::Color::Red, hp) {}

void Monster::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {



}