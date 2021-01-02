#pragma once
#include "enums.h"
#include "Tile.h"
class Actor;

class Action
{
public:
	Action(Actor* user, Actor* target, ACTION_TYPE type);
	Action(Actor* user, ACTION_TYPE type);
	Action(Actor* user, Tile* tile, ACTION_TYPE type);
	~Action() {}

	int GetCost() { return speedCost; }
	Actor* GetUser() { return user; }
	Actor* GetTarget() { return target; }
	ACTION_TYPE GetType() { return type; }
	Tile* GetTile() { return tile; }
protected:
	Actor* user;
	Actor* target = nullptr;
	ACTION_TYPE type;
	Tile* tile;

	int speedCost = 1;
};

