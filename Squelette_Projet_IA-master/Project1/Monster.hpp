#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "Entity.hpp"

class Monster : public Entity {
public:
	Monster(float x, float y);
	void update(float deltaTime, Grid& grid) override;
};

#endif