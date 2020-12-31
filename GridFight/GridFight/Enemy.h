#pragma once
#include "Actor.h"
class Enemy :	public Actor
{
public:
	Enemy(CombatEngine* e, int ID);
	~Enemy() {};
};

