#include "Monster.hpp"
#include <cmath>

using namespace std;
using namespace sf;

Monster::Monster(float x, float y, int hp) : Entity(x, y, Color::Red, hp) {}

void Monster::update(float deltaTime, Grid& grid, vector<Entity*> players) {

	Blackboard blackboard; 
	blackboard.SetValue("PlayerDetected", 0); 

	auto root = make_unique<SelectorNode>(); 
	auto sequence = make_unique<SequenceNode>(); 




	root->execute(); 
	return;

}

void Monster::draw(RenderWindow& window) {
	window.draw(shape);
}