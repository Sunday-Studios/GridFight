#pragma once
#include "GameObject.h"
#include "Tile.h"
#include <vector>

using namespace std;

class CombatGrid
{
public:
	CombatGrid(GameEngine* e);
	~CombatGrid();
	void SetupGrid(int ID);
	void Draw(RenderWindow* w);
protected:
	vector<vector<GameObject*>> grid;
	GameEngine* engine;
	int rows = 0;
	int cols = 0;
};

