#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Boo.h"
#include "Grid.hpp"
#include <vector>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player* player = new Player(200, 400);
    Boo* boo = new Boo(200, 100, 100);
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

        player->update(deltaTime, grid);

        window.clear();
        grid.draw(window);
        window.draw(boo->shape);
        window.draw(player->shape);
        window.display();
    }
    return 0;
}

