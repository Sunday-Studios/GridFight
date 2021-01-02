#pragma once
#include "Actor.h"
class Enemy :	public Actor
{
public:
	Enemy(CombatScreen* e, int ID);
	~Enemy() {};
	bool GetHasTarget() { return bHasTarget; }
	Actor* GetTarget() { return target; }
	void SetTarget(Actor* a) {
		target = a;
		bHasTarget = true;
	}
protected:
	Actor* target;
	bool bHasTarget = false;
};

