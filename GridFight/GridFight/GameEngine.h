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
#include <iostream>
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
	void MouseMoved();

	void SortInitiative(vector<Actor*> units);

	GAME_STATES MainMenuLoop();
	GAME_STATES CharacterSelectLoop();
	GAME_STATES CombatLoop();
	GAME_STATES RewardScreenLoop();

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

	int currentTurn;

	PlayerUnit* selectedPlayerUnit;
	Tile* targetTile;
	vector<Tile*> pathToTarget;
	Actor* highlightActor;

	int currentLevel = 0;

};

