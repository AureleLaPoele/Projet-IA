#ifndef BOO_HPP
#define BOO_HPP

#include <SFML/Graphics.hpp>
#include "Enemy.hpp"


class Boo : public Enemy {
public:
	Boo(float x, float y);
	void update(float deltaTime, Grid& grid) override;
};

#endif
