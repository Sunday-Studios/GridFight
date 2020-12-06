#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class Action;
class Tile;

using namespace sf;
using namespace std;

class Actor : public GameObject
{
public:
	Actor(GameEngine* e);
	~Actor() {};
	virtual void Update(Time t);
	int GetCurrentHealth() { return currentHealth; }
	int GetMaxHealth() { return maxHealth; }
	int GetCurrentSpeed() { return currentSpeed; }
	int GetMaxSpeed() { return maxSpeed; }
	int GetArmour() { return armour; }
	int GetInitiative() { return initiative; }
	std::string GetName() { return name; }
	Tile* GetTile() { return tile; }
	void SetTile(Tile* t) { tile = t; }
	vector<Action*> GetActions() { return actionList; }
	void SetActions(vector<Action*> acts) { actionList = acts; }
	void SetMoveTarget(Tile* t) { moveTarget = t; }
	void SetMoving(bool b) { bIsMoving = b; }
	bool GetMoving() { return bIsMoving; }
	void ResetSpeed() { currentSpeed = maxSpeed; }
protected:
	Tile* tile;
	Tile* moveTarget;
	int currentHealth = 0;
	int maxHealth = 0;
	int currentSpeed = 0;
	int maxSpeed = 0;
	int armour = 0;
	int initiative = 0;
	string name = "";
	vector<Action*> actionList;
	bool bIsMoving = false;
	float moveSpeed = 40;
};

