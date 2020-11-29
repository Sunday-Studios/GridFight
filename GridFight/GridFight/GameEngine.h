#pragma once
#include <SFML/Graphics.hpp>
#include "Action.h"
#include "GameObject.h"
#include "Actor.h"
#include "Enemy.h"
#include "PlayerUnit.h"
#include "Tile.h"
#include "CombatGrid.h"

#include <vector>

using namespace sf;
using namespace std;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	bool IsRunning() { return window->isOpen(); }
	void MainLoop();

protected:
	void Update(Time t);
	void Draw();
	void CreateLevel();
	void InitCombatGrid();
	void MouseClicked();
	void MouseReleased();

	RenderWindow* window;
	View camera;
	Clock clock;

	Vector2i mousePos;

	vector<GameObject*> gameObjects;
	vector<GameObject*> playerUnits;
	vector<GameObject*> enemyUnits;
	vector<Action*> actions;

	CombatGrid* grid;
};

