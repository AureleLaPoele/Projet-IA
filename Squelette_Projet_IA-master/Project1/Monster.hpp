#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "Entity.hpp"
#include "Player.hpp"
#include "Node.h"

using namespace std;
using namespace sf;

// rayon de detection
// deplacement vers le joueur le plus proche
// attaque si joueur a portee
// deplacement aleatoire si pas de joueur a portee

class Monster : public Entity {
public:
	Monster(float x, float y, int hp);
	void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
	void draw(RenderWindow& window) override;
};

#endif