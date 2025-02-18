#include "Boo.h"
#include <iostream>

Boo::Boo(float x, float y, float radius, int hp) : Enemy(x, y, hp), state(BooState::Idle), direction(Direction::EAST) {
	detectionRadius = radius;
}

Boo::~Boo() {
	std::cout << "Un boo est détruit\n";
}

std::string Boo::toString(BooState s) const {
    switch (s) {
        case BooState::Idle:   return "Idle";
        case BooState::Chase:  return "Chase";
        case BooState::Freeze: return "Freeze";
        case BooState::Escape: return "Escape";
    }
    return "Unknown";
}

void Boo::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
    for (auto entity : players) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
            if (isSeenByPlayer(*player)) {
                state = BooState::Freeze; // Si Boo est vu, il se fige
            }
            else {
                state = BooState::Chase; // Sinon, il chasse le joueur
            }

            switch (state) {
            case BooState::Idle:
                // Ne rien faire
                break;

            case BooState::Chase:
                moveTowardsPlayer(*player, 50.0f, deltaTime); // Vitesse = 50 unités/sec
                //std::cout << "Actuellement entrain de chase\n";
                break;

            case BooState::Freeze:
                // Ne pas bouger
                break;

            case BooState::Escape:
                // Logique d'évasion si nécessaire
                break;
            }
        }
    }
    std::cout << toString(state) << std::endl;
    shape.setPosition(pos);
    pos = shape.getPosition();
}

bool Boo::isSeenByPlayer(const Player& player) {
    switch (player.direction) {
    case Direction::NORTH:
        return (this->pos.y < player.pos.y); // Si Boo est au-dessus du joueur
    case Direction::SOUTH:
        return (this->pos.y > player.pos.y); // Si Boo est en dessous du joueur
    case Direction::EAST:
        return (this->pos.x > player.pos.x); // Si Boo est à droite du joueur
    case Direction::WEST:
        return (this->pos.x < player.pos.x); // Si Boo est à gauche du joueur
    default:
        return false;
    }
}

void Boo::moveTowardsPlayer(const Player& player, float speed, float deltaTime) {
    float dx = player.pos.x - pos.x;
    float dy = player.pos.y - pos.y;

    float length = std::sqrt(dx * dx + dy * dy);

    dx /= length;
    dy /= length;

    pos.x += dx * speed * deltaTime;
    pos.y += dy * speed * deltaTime;

    //std::cout << "Le boo bouge\n";
    std::cout << "Boo position : (" << pos.x << ", " << pos.y << ")\n";
}


void Boo::draw(sf::RenderWindow& window) {
	window.draw(shape);
}