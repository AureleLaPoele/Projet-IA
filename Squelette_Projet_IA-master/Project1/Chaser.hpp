#ifndef CHASER_HPP
#define CHASER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

using namespace std;
using namespace sf;

class State {
public:
    bool hasEnergy = false;
    float energies = 100;

    bool energy() const { return hasEnergy; }
    float Getenergies() const { return energies; }

    void SetEnergy(bool energy) { hasEnergy = energy; }
    void Reduceenergies() { energies = max(0.f, energies - 1.2f);}
};

class Action {
public:
    virtual bool CanExecute(const State& state) = 0;
    virtual void Execute(State& state) = 0;
    virtual ~Action() {}
};

enum class Goal {
	Manger,
    Chaser,
};

class EnergyAction : public Action {
public:
    bool CanExecute(const State& state) override { return state.energy() && state.Getenergies() > 0; };
    void Execute(State& state) override;
};

class SearchEnergyAction : public Action {
public:
    bool CanExecute(const State& state) override { return !state.energy(); };
    void Execute(State& state) override;
};

class SearchPlayerAction : public Action {
public:
    bool CanExecute(const State& state) override { return state.Getenergies() > 0; };
    void Execute(State& state) override;
};

class GOAPPlanner { 
public:
    vector<Action*> Plan(const State& initialState, Goal goal) {
        vector<Action*> plan;

        if (goal == Goal::Manger) {
            if (initialState.Getenergies() > 0 && initialState.Getenergies()<=20 && !initialState.energy()) {
                plan.push_back(new SearchEnergyAction());
                plan.push_back(new EnergyAction());
            }
        }
        else if (goal == Goal::Chaser) {
            if (initialState.Getenergies() >= 20) {
                plan.push_back(new SearchPlayerAction()); 
            }
            return plan;
        }
    }
};

class Chaser : public Entity {
private:
    State state;
    GOAPPlanner planner; 
public:
    Chaser(float x, float y, int hp);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
    void draw(RenderWindow& window) override;
};

#endif