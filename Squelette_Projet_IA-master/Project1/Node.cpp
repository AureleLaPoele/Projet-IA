
#include <unordered_map>
#include <string>
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
    NodeMonster execute() override {
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
    NodeMonster execute() override {
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
    NodeMonster execute() override {
        return (blackboard.GetValue(key) == expectedValue) ? NodeMonster::SUCCESS : NodeMonster::FAILURE;
    }
};

//========================================DASH=========================================
class ActionNodeDash : public BTNode {
private:
    string actionDash;
public:
    ActionNodeDash(string name) : actionDash(name) {}
    NodeMonster execute() override {
        cout << "Action: " << actionDash << endl;
        return NodeMonster::SUCCESS;
    }
};


//========================================AA=========================================
class ActionNodeAttack : public BTNode {
private:
	string actionAA;   
public: 
	ActionNodeAttack(string name) : actionAA(name) {}
	NodeMonster execute() override {
		cout << "Action: " << actionAA << endl;
		return NodeMonster::SUCCESS;
	}
};

//========================================SE TP ET LANCE UN PROJECTILE====================
class ActionNodeTP : public BTNode {
private:
	string actionTP;
public:
	ActionNodeTP(string name) : actionTP(name) {}
	NodeMonster execute() override {
		cout << "Action: " << actionTP << endl;
		return NodeMonster::SUCCESS;
	}
};
