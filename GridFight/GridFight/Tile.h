#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "Actor.h"

class Tile :	public GameObject
{
public:
	Tile(GameEngine*, int ID);
	~Tile() {};
	void SetObstacle(int ID);
	void Draw(RenderWindow * w);
	Obstacle* GetObstacle() { return obstacle; };
	bool SetActor(Actor* a);
	Actor* GetActor() { return actor; }
protected:
	Actor* actor;
	Obstacle* obstacle;
};

