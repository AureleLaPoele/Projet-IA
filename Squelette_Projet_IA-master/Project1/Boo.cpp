#include "Boo.h"
#include <iostream>

Boo::Boo(float x, float y, float radius, int hp, float speed) : Enemy(x, y, hp), state(BooState::Idle), direction(Direction::EAST), speed(speed) {
	detectionRadius = radius;
    initialPos.x = x;
    initialPos.y = y;
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

void Boo::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
    for (auto entity : players) {
        Player* player = dynamic_cast<Player*>(entity);
        if (player) {
            if (state != BooState::Escape) {
                if (isSeenByPlayer(*player)) {
                    changeState(BooState::Freeze);
                }
                else {
                    changeState(BooState::Chase);
                }
            }

            switch (state) {
            case BooState::Idle:
                break;

            case BooState::Chase:
                moveTowardsPlayer(*player, speed, deltaTime);
                break;

            case BooState::Freeze:
                break;

            case BooState::Escape:
                moveTowardsInitialPosition(speed, deltaTime);
                if (isInInitialPos()) {
                    changeState(BooState::Idle);
                }
                else {
                    std::cout << "Pas encore a pos initial\n";
                }
                break;
            }
        }
    }
    booChase.setPosition(pos);
    booFreeze.setPosition(pos);
    pos = booChase.getPosition();
    pos = booFreeze.getPosition();
    setBooOrientation();
    attack(players);
    //std::cout << booChase.getPosition().x << " " << booChase.getPosition().y << std::endl;
}

bool Boo::isInInitialPos() {
    if (pos.x <= 105.0f && pos.x >= 95.0f) {
        return true;
    }
    else {
        return false;
    }
}
void Boo::attack(std::vector<Entity*>players) {
    for (auto& player : players) {
        if (player = dynamic_cast<Player*>(player)) {
            if (attackCD.getElapsedTime() >= cooldownTime) {
                if (player->isAlive() && (booChase.getGlobalBounds().intersects(player->shape.getGlobalBounds()) || booFreeze.getGlobalBounds().intersects(player->shape.getGlobalBounds()))) {
                    player->takeDamage(DAMAGE);
                    std::cout << "Enemy attacks" << std::endl;
                    std::cout << "Player HP: " << player->health << std::endl;
                    attackCD.restart();
                    changeState(BooState::Escape);
                }
            }
        }
    }
}

void Boo::changeState(BooState newState) {
    if (state != newState && newState == BooState::Chase) {
        state = BooState::Chase;
    } else if (state != newState && newState == BooState::Freeze) {
        state = BooState::Freeze;
    } else if (state != newState && newState == BooState::Escape) {
        state = BooState::Escape;
    } else if (state != newState && newState == BooState::Idle) {
        state = BooState::Idle;
    }
}

bool Boo::isSeenByPlayer(const Player& player) {
    switch (player.direction) {
    case Direction::NORTH:
        return (this->pos.y > player.pos.y); // Si Boo est au-dessus du joueur
    case Direction::SOUTH:
        return (this->pos.y < player.pos.y); // Si Boo est en dessous du joueur
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

    setDirection(dx, dy);
}

void Boo::moveTowardsInitialPosition(float speed, float deltaTime) {
    speed *= 5;
    float dx = initialPos.x - pos.x;
    float dy = initialPos.y - pos.y;

    float length = std::sqrt(dx * dx + dy * dy);

    dx /= length;
    dy /= length;

    pos.x += dx * speed * deltaTime;
    pos.y += dy * speed * deltaTime;

    setDirection(dx, dy);
}

void Boo::setDirection(float dx, float dy) {
    if (dx > 0) {
        direction = Direction::EAST;
    }
    else if (dx < 0) {
        direction = Direction::WEST;
    }
}

void Boo::setBooOrientation() {
    if (direction == Direction::EAST) {
        booChase.setScale(-2, 2);
        booFreeze.setScale(-2, 2);
    }
    else {
        booChase.setScale(2, 2);
        booFreeze.setScale(2, 2);
    }
}

void Boo::draw(sf::RenderWindow& window) {
    if (state == BooState::Chase) window.draw(booChase);
    else if (state == BooState::Freeze) window.draw(booFreeze);
    else if (state == BooState::Escape) window.draw(booFreeze);
}