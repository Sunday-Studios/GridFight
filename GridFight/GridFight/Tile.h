#pragma once
#include "GameObject.h"
#include "Obstacle.h"
#include "Actor.h"

class Tile :	public GameObject
{
public:
	Tile(GameEngine*, int ID, int r, int c);
	~Tile() {};
	void SetObstacle(int ID);
	void Draw(RenderWindow * w);
	void Update(Time t);
	Obstacle* GetObstacle() { return obstacle; };
	bool SetActor(Actor* a);
	Actor* GetActor() { return actor; }
	bool GetHasActor() { return bHasActor; }
	int GetRow() { return row; }
	int GetCol() { return col; }
	int GetMoveCost() { 
		if(bHasObstacle) return obstacle->GetMoveCost();
		return 1;
	}
	void SetHighlighted(bool b) { bIsHighlighted = b; }
protected:
	Clock clock;
	Actor* actor = NULL;
	Obstacle* obstacle;
	bool bHasActor = false;
	bool bHasObstacle = false;
	int row;
	int col;
	bool bIsHighlighted = false;
};

