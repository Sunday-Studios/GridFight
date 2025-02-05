#pragma once
#include "GameObject.h"
#include "Tile.h"
#include "PlayerUnit.h"
#include "Enemy.h"
#include <iostream>
#include <vector>

using namespace std;

class CombatGrid
{
public:
	CombatGrid(CombatScreen* e);
	~CombatGrid();
	void SetupGrid(int ID);
	void Draw(RenderWindow* w);
	void Update(Time t);
	void AddActor(PlayerUnit* p);
	void AddActor(Enemy* e);
	Tile* GetTile(Vector2i mousePos);
	Tile* GetTile(Actor* actor);
	vector<Tile*> GetMeleePath(Tile* start, Tile* end);
protected:


	class Path {
	public:
		vector<Tile*> path;
		int totalCost = 0;
		int remainingCost = 0;
		int pathCost = 0;
	};
	int GetPathCost(vector<Tile*> path);
	vector<Path> InsertPath(vector<Path> pathList, Path newPath);
	//void AddPath(Path currentPath, Tile* tile);
	


	vector<vector<Tile*>> grid;
	CombatScreen* engine;
	int rows = 0;
	int cols = 0;

	Sprite gridBackground;
	Texture texGridBack;
};

