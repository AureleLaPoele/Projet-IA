#include "Boo.h"

Boo::Boo(float x, float y, float radius) : Enemy(x, y) {
	detectionRadius = radius;
}

void Boo::update(float deltaTime, Grid& grid) {

}

bool Boo::detectPlayer(float playerPosX, float playerPosY) {
	return true;
}