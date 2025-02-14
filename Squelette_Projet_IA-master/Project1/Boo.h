#ifndef BOO_HPP
#define BOO_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"


class Boo : public Enemy {
public:
	float detectionRadius;

	Boo(float x, float y, float radius);

	void update(float deltaTime, Grid& grid) override;
	bool detectPlayer(float playerPosX, float playerPosY);
};

#endif
