#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Boo.h"
#include "Grid.hpp"
#include "Monster.hpp"
#include <vector>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    std::vector<Entity*> players;
    players.push_back(new Player(200, 400, 100));

    std::vector<Entity*> enemies;
    enemies.push_back(new Boo(100, 100, 100, 25));

    Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        grid.draw(window);
        for (const auto& player : players) {
            if (player->isAlive()) {
                player->update(deltaTime, grid, enemies);
                player->draw(window);
            }
        }
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                enemy->update(deltaTime, grid, players);
                enemy->draw(window);
            }
        }
        window.display();
    }
    return 0;
}

