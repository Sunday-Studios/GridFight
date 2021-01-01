#pragma once
#include <SFML/Graphics.hpp>
#include "Action.h"
#include "GameObject.h"
#include "Actor.h"
#include "Enemy.h"
#include "PlayerUnit.h"
#include "Tile.h"
#include "CombatGrid.h"
#include "enums.h"
#include "InspectPane.h"
#include "ActionBar.h"
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

class CombatEngine
{
public:
	CombatEngine(RenderWindow* w);
	~CombatEngine();
	bool IsRunning() { return window->isOpen(); }
	void MainLoop();

protected:
	void Init();
	void Update(Time t);
	void Draw();
	void CreateLevel();
	void InitCombatGrid();
	void MouseClicked();
	void MouseReleased();
	void MouseMoved();

	void SortInitiative(vector<Actor*> units);
	void ConvertPathToActions(Actor* currentTurn);
	void DoAction(Action* action);

	
	void AdvanceTurn();
	void AITurn(Enemy* enemy);

	GAME_STATES CombatLoop();


	GAME_STATES currentState = MAIN_MENU;

	RenderWindow* window;
	View camera;
	Clock clock;

	Vector2i mousePos;

	vector<Actor*> combatUnits;
	vector<PlayerUnit*> playerUnits;
	vector<Enemy*> enemyUnits;
	vector<Action*> actions;

	CombatGrid* grid;

	int currentTurn = 0;

	PlayerUnit* selectedPlayerUnit;
	Tile* targetTile;
	vector<Tile*> pathToTarget;
	Actor* highlightActor;
	InspectPane* inspectPane;
	ActionBar* actionBar;


	int currentLevel = 0;
	bool bDoingAction = false;
	bool bIsPlayerTurn = false;
	bool bStartOfTurnWait = false;
	bool bEndTurn = false;
};

