// player.cpp
#include "Player.hpp"
#include "Enemy.hpp"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

Player::Player(float x, float y, int hp) : Entity(x, y, sf::Color::Blue, hp), attackTimer(0.f), direction(Direction::NONE) {
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    directionShape.setSize({ 15, 15 });
    directionShape.setOrigin(15 / 2, 15 / 2);
    directionShape.setPosition(pos.x, pos.y);
    directionShape.setFillColor(sf::Color::Red);
}

Player::~Player() {
    std::cout << "Le joueur est détruit\n";
}

void Player::update(float deltaTime, Grid& grid, std::vector<Entity*> enemies) {
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        movement.y -= SPEED * deltaTime;
        direction = Direction::SOUTH;
        directionShape.setPosition(pos.x, pos.y - 10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += SPEED * deltaTime;
        direction = Direction::NORTH;
        directionShape.setPosition(pos.x, pos.y + 10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        movement.x -= SPEED * deltaTime;
        direction = Direction::WEST;
        directionShape.setPosition(pos.x - 10, pos.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += SPEED * deltaTime;
        direction = Direction::EAST;
        directionShape.setPosition(pos.x + 10, pos.y);
    }

    // Boucle pour ranger les diagonales pour le shape rouge
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            directionShape.setPosition(pos.x + 10, pos.y - 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            directionShape.setPosition(pos.x - 10, pos.y - 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            directionShape.setPosition(pos.x + 10, pos.y + 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            directionShape.setPosition(pos.x - 10, pos.y + 10);
        }
        break;
    } 

    sf::Vector2f newPosition = shape.getPosition() + movement;
    sf::FloatRect newBounds(newPosition, shape.getSize());

    // Vérifier les quatre coins du joueur
    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    float halfWidth = shape.getSize().x / 2;
    float halfHeight = shape.getSize().y / 2;

    if (isWalkable(newPosition.x - halfWidth, newPosition.y - halfHeight) &&
        isWalkable(newPosition.x + halfWidth - 1, newPosition.y - halfHeight) &&
        isWalkable(newPosition.x - halfWidth, newPosition.y + halfHeight - 1) &&
        isWalkable(newPosition.x + halfWidth - 1, newPosition.y + halfHeight - 1)) {
        shape.move(movement);
        pos = shape.getPosition();
        directionShape.move(movement);
    }

    attackTimer += deltaTime;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && attackTimer >= ATTACK_COOLDOWN) {
        attack(enemies);
        attackTimer = 0.f;
    }
}

void Player::attack(std::vector<Entity*>enemies) {
    for (auto& enemy : enemies) {
        if (enemy = dynamic_cast<Enemy*>(enemy)) {
            if (enemy->isAlive() && shape.getGlobalBounds().intersects(enemy->shape.getGlobalBounds())) {
                enemy->takeDamage(DAMAGE);
                std::cout << "Enemy HP: " << enemy->health << std::endl;
            }
        }

    }
    std::cout << "Player attacks" << std::endl;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(directionShape);
}