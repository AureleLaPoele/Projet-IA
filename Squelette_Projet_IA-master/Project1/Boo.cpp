#include "Boo.h"
#include <iostream>

Boo::Boo(float x, float y, float radius, int hp) : Enemy(x, y, hp), state(BooState::Idle) {
	detectionRadius = radius;
}

Boo::~Boo() {
	std::cout << "Un boo est détruit\n";
}

void Boo::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
    for (auto entity : players) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
            directionVerifier(*player);
        }
    }
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

void Boo::changeState(BooState newState) {
	if (state != newState) {
		state = newState;
		std::cout << "Boo change d'état : " << static_cast<int>(newState) << std::endl;
	}
}

void Boo::directionVerifier(Player& player) {
    if (player.direction == direction) {
        std::cout << "Le boo et le joueur regarde dans la meme direction\n";
    }
}

void Boo::draw(sf::RenderWindow& window) {
	window.draw(shape);
}