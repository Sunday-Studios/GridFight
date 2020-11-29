#pragma once
#include "Actor.h"
class Enemy :	public Actor
{
public:
	Enemy(GameEngine* e, int ID);
	~Enemy() {};
};

