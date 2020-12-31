#pragma once
#include "GameObject.h"
class Obstacle :	public GameObject
{
public:
	Obstacle(CombatEngine* e, int ID);
	~Obstacle() {}
	int GetMoveCost() { return moveCost; }
protected:
	int moveCost = 1;
};

