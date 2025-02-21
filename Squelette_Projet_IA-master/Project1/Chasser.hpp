#ifndef CHASSER_HPP
#define CHASSER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Grid.hpp"
#include "Monster.hpp"

using namespace std;
using namespace sf;

class Chasser : public Entity {
public:
    Chasser(float x, float y, int hp);
    void update(float deltaTime, Grid& grid, vector<Entity*> players) override; 
    void draw(RenderWindow& window) override;

    bool hasEnergy = false;
    bool chasserPlayer = true;
    float energies = 100;
    bool green = false;

    bool energy() const { return hasEnergy; }
    bool GetChasserPlayer() const { return chasserPlayer; }
    float Getenergies() const { return energies; }

    void SetEnergy(bool energy) { hasEnergy = energy; }
    void SetChasserPlayer(bool chasserPlayer) { chasserPlayer = GetChasserPlayer(); }
    void Reduceenergies() { energies = max(0.f, energies - 0.1f); }
    void Increaseenergies() { energies = max(100.f, energies + 1.0f); }
    void Setenergies(int level) { energies = level; }
};

class Action {
public:
    virtual bool CanExecute(const Chasser& state) = 0;
    virtual void Execute(Chasser& state, const vector<Entity*>& players) = 0;
    virtual ~Action() {}
};

enum class Goal {
    Chasser,
	Manger,
};

class EnergyAction : public Action {
public:
    bool CanExecute(const Chasser& state) override { return state.energy(); };
    void Execute(Chasser& state, const vector<Entity*>& players);
};

class SearchEnergyAction : public Action {
public:
    bool CanExecute(const Chasser& state) override { return true; };
    void Execute(Chasser& state, const vector<Entity*>& players);
};

class SearchPlayerAction : public Action {
public:
    bool CanExecute(const Chasser& state) override { return true; };
    void Execute(Chasser& state, const vector<Entity*>& players);
};

class GOAPPlanner {
public:
    vector<Action*> Plan(Chasser& initialState, Goal goal) {
        vector<Action*> plan;

        if (goal == Goal::Manger) {
            if (!initialState.energy()) {
                plan.push_back(new SearchEnergyAction());
                plan.push_back(new EnergyAction());
            }
            if (initialState.energies == 100)
            {
                initialState.chasserPlayer = true;
            }
        }
        else if (goal == Goal::Chasser){
            plan.push_back(new SearchPlayerAction()); 
            return plan;
        }
    }
};

#endif