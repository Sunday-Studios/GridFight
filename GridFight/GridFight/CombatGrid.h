#pragma once
#include "GameObject.h"
#include "Tile.h"
#include "PlayerUnit.h"
#include "Enemy.h"
#include <vector>

using namespace std;

class CombatGrid
{
public:
	CombatGrid(GameEngine* e);
	~CombatGrid();
	void SetupGrid(int ID);
	void Draw(RenderWindow* w);
	void AddActor(PlayerUnit* p);
	void AddActor(Enemy* e);
protected:
	vector<vector<Tile*>> grid;
	GameEngine* engine;
	int rows = 0;
	int cols = 0;
};

