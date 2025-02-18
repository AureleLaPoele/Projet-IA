#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Player.hpp"

using namespace std;

class NodeMonster {};

class BTNode {
	virtual NodeMonster execute() = 0;
};

class Blackboard {
public:
	void SetValue(const string& key, int value) {}
	int GetValue(const string& key) { return 0; }
};

class SequenceNode : public BTNode {
public:
	void Addmonster(unique_ptr<BTNode> monster) {}
	NodeMonster execute() override { return NodeMonster(); }
};

class SelectorNode : public BTNode {
public:
	void Addmonster(unique_ptr<BTNode> monster) {}
	NodeMonster execute() override { return NodeMonster(); }
};

class ConditionNode : public BTNode {
public:
	ConditionNode(Blackboard& bb, const string& key, int value) : blackboard(bb), key(key), expectedValue(value) {}
	NodeMonster execute()  override { return NodeMonster(); }
	Blackboard& blackboard;
	string key;
	int expectedValue;
};

class ActionNode : public BTNode {
public:
	ActionNode(string name) : actionDash(name) {}
	NodeMonster execute() override { return NodeMonster(); }
private:
	string actionDash;
};
