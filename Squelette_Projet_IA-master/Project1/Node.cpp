#include "Player.hpp"
#include <unordered_map>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

enum class NodeMonster { SUCCESS, FAILURE };

class BTNode {
public:
    virtual ~BTNode() = default;
    virtual NodeMonster execute() = 0;
};

class Blackboard {
private:
    unordered_map<string, int> data;
public:
    void SetValue(const string& key, int value) {
        data[key] = value;
    }
    int GetValue(const string& key) {
        return data[key];
    }
};

class SequenceNode : public BTNode {
private:
    vector<unique_ptr<BTNode>> monsters;
public:
    void Addmonster(unique_ptr<BTNode> monster) {
        monsters.push_back(move(monster));
    }
    NodeMonster execute() {
        for (auto& monster : monsters) {
            if (monster->execute() == NodeMonster::FAILURE) {
                return NodeMonster::FAILURE;
            }
        }
        return NodeMonster::SUCCESS;
    }
};

class SelectorNode : public BTNode {
private:
    vector<unique_ptr<BTNode>> monsters;
public:
    void Addmonster(unique_ptr<BTNode> monster) {
        monsters.push_back(move(monster));
    }
    NodeMonster execute() {
        for (auto& monster : monsters) {
            if (monster->execute() == NodeMonster::SUCCESS) {
                return NodeMonster::SUCCESS; 
            }
        }
        return NodeMonster::FAILURE;
    }
};

class ConditionNode : public BTNode {
public:
    Blackboard& blackboard;
    string key;
    int expectedValue;
    ConditionNode(Blackboard& bb, const string& key, int value) : blackboard(bb), key(key), expectedValue(value) {}
    NodeMonster execute() {
        return (blackboard.GetValue(key) < expectedValue) ? NodeMonster::SUCCESS : NodeMonster::FAILURE;
    }
};

class ActionNode : public BTNode {
private:
    string actions;
public:
    ActionNode(string name) : actions(name) {}
    NodeMonster execute() override {
		if (actions == "Dash") {
			cout << "actions: " << endl;
		}
		else if (actions == "AA") {
			cout << "ActionAA: " << endl;
		}
		else if (actions == "TP") {
			cout << "ActionTP: " << endl;
		}
		else if (actions == "Patrouille") {
			cout << "ActionPatrouille: " << endl;
		}
        return NodeMonster::SUCCESS;
    }
};
