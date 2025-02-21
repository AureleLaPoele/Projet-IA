#ifndef BOO_HPP
#define BOO_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Player.hpp"

enum class BooState { Idle, Chase, HalfChase, Freeze, Escape };

class Boo : public Enemy {
public:
	sf::Vector2f initialPos;
	sf::Texture booChaseTexture;
	sf::Texture booFreezeTexture;
	sf::Sprite booChase;
	sf::Sprite booFreeze;
	Direction direction;
	BooState state;
	float speed;
	float detectionRadius;
	sf::Clock attackCD;
	sf::Time cooldownTime = sf::seconds(1.0f);
	static constexpr int DAMAGE = 20;

	Boo(float x, float y, float radius, int hp, float speed);
	~Boo();
	void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
	void draw(sf::RenderWindow& window) override;
	bool isSeenByPlayer(const Player& player);
	void moveTowardsPlayer(const Player& player, float speed, float deltaTime);
	void setDirection(float dx, float dy);
	void setBooOrientation();
	void attack(std::vector<Entity*>players);
	void moveTowardsInitialPosition(float speed, float deltaTime);
	void changeState(BooState newState);
	bool isInInitialPos();
};

#endif
