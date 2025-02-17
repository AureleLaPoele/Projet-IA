#ifndef BOO_HPP
#define BOO_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"

enum class BooState { Idle, Chase, Freeze, Escape };

class Boo : public Enemy {
public:
	BooState state;
	float detectionRadius;

	Boo(float x, float y, float radius, int hp);

	void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
	bool detectPlayer(float playerPosX, float playerPosY);
	void draw(sf::RenderWindow& window) override;
};

#endif
