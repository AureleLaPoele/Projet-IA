#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "Entity.hpp"

class Monster : public Entity {
public:
	Monster(float x, float y, int hp);
	void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
};

#endif