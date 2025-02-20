#include "Chaser.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;



// ================================================================================================
Chaser::Chaser(float x, float y, int hp) : Entity(x, y, Color::Red, hp) {}

void Chaser::update(float deltaTime, Grid& grid, vector<Entity*> player) {}

void Chaser::draw(RenderWindow& window) {    
	window.draw(shape);  
}
//================================================================================================
class GOAPPlanner {
public:
    vector<Action*> Plan(const State& initialState, Goal goal) {
    vector<Action*> plan;

        if (goal == Goal::Manger) {
            if (initialState.Getenergies() > 0 && !initialState.energy()) { 
                plan.push_back(new SearchEnergyAction());
                plan.push_back(new EnergyAction());  
            } 
            else if (initialState.energy()) { 
                plan.push_back(new EnergyAction()); 
            }
        }
		else if (goal == Goal::Chaser) {
			if (initialState.Getenergies() > 0) {
				plan.push_back(new SearchPlayerAction());
			}
		}
        return plan;
    }
};

class EnergyAction : public Action {
public:
    bool CanExecute(const State& state) override {return state.energy() && state.Getenergies() > 0;}

    void Execute(State& state) override {
		//Reste à côte de l'ennemi pour se recharger
        cout << "L'agent mange.\n";
        state.Reduceenergies();
        state.SetEnergy(false);
    }
};

class SearchEnergyAction : public Action {
public:
    bool CanExecute(const State& state) override {return !state.energy(); }

    void Execute(State& state) override {
		//chercher l'ennemi le plus proche pour se recharger
        cout << "L'agent cherche de la nourriture.\n";
        state.SetEnergy(true);
    }
};

class SearchPlayerAction : public Action { 
public:
    bool CanExecute(const State& state) override {return state.Getenergies() >= 20;}

    void Execute(State& state) override {
        cout << "L'agent cherche un joueur.\n";
        //chase le joueur
    }
};