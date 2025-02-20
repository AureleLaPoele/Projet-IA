#include "Chaser.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

Chaser::Chaser(float x, float y, int hp) : Entity(x, y, Color::Red, hp) {}

void Chaser::update(float deltaTime, Grid& grid, vector<Entity*> player) {





}

void Chaser::draw(RenderWindow& window) {    
	window.draw(shape);  
}

void EnergyAction:: Execute(State& state) {
	//Reste à côte de l'ennemi pour se recharger
    cout << "L'agent mange.\n";
    state.Reduceenergies();
    state.SetEnergy(false);
}

void SearchEnergyAction:: Execute(State& state)  {
		//chercher l'ennemi le plus proche pour se recharger
        cout << "L'agent cherche de la nourriture.\n";
        state.SetEnergy(true);
};

void SearchPlayerAction::Execute(State& state) {
        cout << "L'agent cherche un joueur.\n";
        //chase le joueur
};