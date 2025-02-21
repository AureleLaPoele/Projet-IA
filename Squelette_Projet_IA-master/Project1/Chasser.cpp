#include "Chasser.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

Chasser::Chasser(float x, float y, int hp) : Entity(x, y, Color::Red, hp) {}

void Chasser::update(float deltaTime, Grid& grid, vector<Entity*> players) {
    GOAPPlanner planner;
	Goal currentGoal;
     
    if (Getenergies() > 20 && GetChasserPlayer()) {
		currentGoal = Goal::Chasser;
    }
	else {
		currentGoal = Goal::Manger;
		chasserPlayer = false;
	}

    vector<Action*> actions = planner.Plan(*this, currentGoal);

    for (Action* action : actions) {
        if (action->CanExecute(*this)) {
            action->Execute(*this,players);
            break;
        }
    }
}

void Chasser::draw(RenderWindow& window) {    
	window.draw(shape);
}

void EnergyAction:: Execute(Chasser& state, const vector<Entity*>& players) {
    state.Increaseenergies();
}

void SearchEnergyAction::Execute(Chasser& state, const vector<Entity*>& players) {

    Vector2f direction = players[0]->shape.getPosition() - state.shape.getPosition();// probleme ici, il faut récupérer la pos du monster

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
    }

    float speed = 250.0f;
    state.velocity = direction * speed;
    state.shape.move(state.velocity);
    state.Reduceenergies();
}

void SearchPlayerAction::Execute(Chasser& state, const vector<Entity*>& players) {
   if (players.empty()) {  
       return;  
   } 

   static Clock clock;  
   Time dt = clock.restart();  
   float deltaTime = dt.asSeconds();  
   float speed = 150.0f;  

   Entity* targetPlayer = players[0];  

   Vector2f direction = targetPlayer->shape.getPosition() - state.shape.getPosition();  
   float length = sqrt(direction.x * direction.x + direction.y * direction.y);  

   if (length != 0) {  
       direction /= length;  
   }  

   state.velocity = direction * speed * deltaTime;  
   state.shape.move(state.velocity);  

   if (length <= 150) {  
       state.green = true;
       state.shape.setFillColor(Color::Green);
   }
   if (length > 150) {
       state.green = false;
       state.shape.setFillColor(Color::Red);
   }

   state.Reduceenergies();
}
