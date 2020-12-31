#pragma once
#include "Actor.h"
class PlayerUnit :	public Actor
{
public:
	PlayerUnit(CombatEngine* e, int ID);
	~PlayerUnit() {};
};

