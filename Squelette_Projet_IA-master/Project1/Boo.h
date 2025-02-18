#ifndef BOO_HPP
#define BOO_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Player.hpp"

enum class BooState { Idle, Chase, Freeze, Escape };

class Boo : public Enemy {
public:
	std::string direction = "WEST";
	BooState state;
	float speed;
	float detectionRadius;

	Boo(float x, float y, float radius, int hp);
	~Boo();
	void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
	void draw(sf::RenderWindow& window) override;
	void changeState(BooState newState);
	void directionVerifier(Player& player);
};

#endif
