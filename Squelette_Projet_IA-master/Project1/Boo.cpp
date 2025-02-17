#include "Boo.h"

Boo::Boo(float x, float y, float radius, int hp) : Enemy(x, y, hp) {
	detectionRadius = radius;
}

void Boo::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {

}

bool Boo::detectPlayer(float playerPosX, float playerPosY) {
	return true;
}

void Boo::draw(sf::RenderWindow& window) {
	window.draw(shape);
}