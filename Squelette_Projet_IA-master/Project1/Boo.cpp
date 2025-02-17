#include "Boo.h"
#include "Player.hpp"
#include <iostream>

Boo::Boo(float x, float y, float radius, int hp) : Enemy(x, y, hp), state(BooState::Idle) {
	detectionRadius = radius;
}

Boo::~Boo() {
	std::cout << "Un boo est détruit\n";
}
void Boo::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
	switch (state) {
	case BooState::Idle:
		break;
	case BooState::Chase:
		break;
	case BooState::Freeze:
		break;
	case BooState::Escape:
		break;
	}
}

bool hasSameDirection(Player& player) {
	if (player.direction == direction)
}

bool Boo::detectPlayer(float playerPosX, float playerPosY) {
	return true;
}

void Boo::draw(sf::RenderWindow& window) {
	window.draw(shape);
}