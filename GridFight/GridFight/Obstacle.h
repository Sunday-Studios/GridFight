#pragma once
#include "GameObject.h"
class Obstacle :	public GameObject
{
public:
	Obstacle(GameEngine* e, int ID);
	~Obstacle() {}
	int GetMoveCost() { return moveCost; }
protected:
	int moveCost = 1;
};

