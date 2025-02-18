#include "Monster.hpp"
#include "PLayer.hpp"
#include <cmath>

using namespace std;
using namespace sf;

Monster::Monster(float x, float y, int hp) : Entity(x, y, Color::Red, hp) {}

void Monster::update(float deltaTime, Grid& grid, vector<Entity*> player) {

	Blackboard blackboard; 

	float distancePM;
	float dx = player[0]->pos.x - this->pos.x;
	float dy = player[0]->pos.y - this->pos.y;
	distancePM = sqrt(dx * dx + dy * dy);
	blackboard.SetValue("PlayerDetected", distancePM);

	int attackChoix = 1;	
	blackboard.SetValue("AttackChoix", attackChoix);

	auto root = make_unique<SelectorNode>();
	auto sequence = make_unique<SequenceNode>(); 

	sequence->Addmonster(make_unique<ConditionNode>(blackboard, "PlayerDetected", 200));
	sequence->Addmonster(make_unique<ActionNode>("Dash"));


	root->Addmonster(move(sequence));
	root->Addmonster(make_unique<ActionNode>("Patrouille"));

	root->execute();
	return;

}

void Monster::draw(RenderWindow& window) {
	window.draw(shape);
}