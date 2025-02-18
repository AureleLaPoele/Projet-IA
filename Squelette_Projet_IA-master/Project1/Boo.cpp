#include "Boo.h"
#include <iostream>

Boo::Boo(float x, float y, float radius, int hp) : Enemy(x, y, hp), state(BooState::Idle), direction(Direction::EAST) {
	detectionRadius = radius;
    if (!booChaseTexture.loadFromFile("assets/Boo/Boo_Chase.png")) {
        std::cerr << "Erreur lors du chargement de la texture du Boo qui chasse.\n";
    }
    if (!booFreezeTexture.loadFromFile("assets/Boo/Boo_Freeze.png")) {
        std::cerr << "Erreur lors du chargement de la texture du Boo qui se cache.\n";
    }
    booChase.setTexture(booChaseTexture);
    booFreeze.setTexture(booFreezeTexture);
    booChase.setPosition(pos);
    booFreeze.setPosition(pos);
    booChase.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    booFreeze.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    booChase.setScale(2, 2);
    booFreeze.setScale(2, 2);
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
                changeState(BooState::Freeze);
                //state = BooState::Freeze; // Si Boo est vu, il se fige
            }
            else {
                changeState(BooState::Chase);
                //state = BooState::Chase; // Sinon, il chasse le joueur
            }

            switch (state) {
            case BooState::Idle:
                shape.setFillColor(sf::Color::Green);
                break;

            case BooState::Chase:
                moveTowardsPlayer(*player, 50.0f, deltaTime);
                shape.setFillColor(sf::Color::Red);
                break;

            case BooState::Freeze:
                shape.setFillColor(sf::Color::White);
                break;

            case BooState::Escape:
                break;
            }
        }
    }
    //std::cout << toString(state) << std::endl;
    booChase.setPosition(pos);
    booFreeze.setPosition(pos);
    pos = booChase.getPosition();
    pos = booFreeze.getPosition();
}

void Boo::changeState(BooState newState) {
    if (state != newState && newState == BooState::Chase) {
        state = BooState::Chase;
        std::cout << "Le boo vous poursuit\n";
    } else if (state != newState && newState == BooState::Freeze) {
        state = BooState::Freeze;
        std::cout << "Le boo se cache\n";
    }
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
}


void Boo::draw(sf::RenderWindow& window) {
    if (state == BooState::Chase) window.draw(booChase);
    else if (state == BooState::Freeze) window.draw(booFreeze);
}