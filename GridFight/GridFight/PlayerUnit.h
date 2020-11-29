#pragma once
#include "Actor.h"
class PlayerUnit :	public Actor
{
public:
	PlayerUnit(GameEngine* e, int ID);
	~PlayerUnit() {};
};

