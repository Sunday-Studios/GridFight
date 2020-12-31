#include "CombatEngine.h"


CombatEngine::CombatEngine(RenderWindow* w) {
	window = w;
	camera = window->getDefaultView();
	Init();
}

CombatEngine::~CombatEngine() {

}

void CombatEngine::Init() {
	CreateLevel();
	InitCombatGrid();
	currentState = COMBAT_SCREEN;
}

void CombatEngine::MainLoop() {
	CombatLoop();
	
}


GAME_STATES CombatEngine::CombatLoop() {
	Event event;
	while (window->isOpen()) {
		Time elapsed = clock.restart();
		window->setView(camera);
		Update(elapsed);
		Draw();
		Actor* currentUnit = combatUnits[currentTurn];
		if (!bDoingAction && currentUnit->GetActions().size() != 0) {
			if (currentUnit->GetCurrentSpeed() > 0) {
				if (currentUnit->GetActions()[0]->GetCost() <= currentUnit->GetCurrentSpeed()) {
					DoAction(currentUnit->GetActions()[0]);
				}
			}
			else {
				AdvanceTurn();
			}
		}
		else if (bDoingAction) {
			if (!currentUnit->GetMoving()) {
				bDoingAction = false;
			}
		}
		if (currentUnit->GetCurrentSpeed() == 0) {
			AdvanceTurn();
		}
		while (window->pollEvent(event)) {
			
			if (event.type == sf::Event::Closed) window->close();
			
			if (!bDoingAction) {
				if (event.type == Event::MouseButtonPressed) {
					mousePos = Vector2i(window->mapPixelToCoords(Mouse::getPosition(*window)));
					MouseClicked();
				}
				if (event.type == Event::MouseButtonReleased) {
					mousePos = Vector2i(window->mapPixelToCoords(Mouse::getPosition(*window)));
					MouseReleased();
				}
				if (event.type == Event::MouseMoved) {
					mousePos = Vector2i(window->mapPixelToCoords(Mouse::getPosition(*window)));
					MouseMoved();
				}
				if (event.type == Event::KeyPressed) {
					if (Keyboard::isKeyPressed(Keyboard::Space)) {
						AdvanceTurn();
					}
				}
			}
			if (event.type == Event::MouseMoved) {
				mousePos = Vector2i(window->mapPixelToCoords(Mouse::getPosition(*window)));
				MouseMoved();
			}

		}
	}
	return MAIN_MENU;
}

void CombatEngine::ConvertPathToActions(Actor* currentTurn) {
	vector<Action*> actionList;
	for (int i = pathToTarget.size()-1; i >=0; i--) {
		Tile* tile = pathToTarget[i];
		if (tile->GetHasActor()) {
			if (tile->GetActor()->GetType() != currentTurn->GetType()) {
				// ACTUALLY CHECK CURRENT SELECTED ATTACK OPTION (e.g. Club, gun, etc);
				Action* action = new Action(currentTurn, tile->GetActor(), ATTACK);
				actionList.push_back(action);
			}
		}
		else {
			Action* action = new Action(currentTurn, tile,MOVE);
			actionList.push_back(action);
		}

	}
	currentTurn->SetActions(actionList);


}

void CombatEngine::DoAction(Action* action) {
	bDoingAction = true;
	Weapon* w;
	switch (action->GetType()) {
	case MOVE:
		action->GetUser()->SetMoveTarget(action->GetTile());
		action->GetUser()->SetMoving(true);
		break;
	case ATTACK:
		action->GetUser()->SetAttacking(true);
		break;
	case SPECIAL:
		break;
	}
}

void CombatEngine::MouseClicked() {
	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		targetTile = grid->GetTile(mousePos);
		if (targetTile != NULL && targetTile->GetHasActor()) {
			Actor* actor = targetTile->GetActor();
			if (actor->GetType() == PLAYER) {
				selectedPlayerUnit = (PlayerUnit*)actor;
			}
		}

	}
	else if (Mouse::isButtonPressed(Mouse::Button::Right) && bIsPlayerTurn) {
		targetTile = grid->GetTile(mousePos);
		if (targetTile!= NULL) {
			for (Tile* t : pathToTarget) {
				t->SetHighlighted(false);
			}
			pathToTarget = grid->GetPath(selectedPlayerUnit->GetTile(), targetTile);
			pathToTarget.pop_back();
			ConvertPathToActions(combatUnits[currentTurn]);

		}
		for (Tile* t : pathToTarget) {
			t->SetHighlighted(true);
		}
	}
	Actor* currentActor = combatUnits[currentTurn];
	
}

void CombatEngine::AdvanceTurn() {
	
	currentTurn++;
	if (currentTurn == combatUnits.size()) {
		currentTurn = 0;
	}
	Actor* currentActor = combatUnits[currentTurn];
	currentActor->ResetSpeed();
}

void CombatEngine::MouseReleased() {
	// do whatever action is queued? might need to think about logic
}

void CombatEngine::MouseMoved() {
	targetTile = grid->GetTile(mousePos);
	if (targetTile != NULL) {
		Actor* actor = targetTile->GetActor();
		if (actor) {
			highlightActor = new Actor(actor);
			inspectPane.SetActor(highlightActor);
		}
	}
	
}

void CombatEngine::CreateLevel() {
	// load a level's details
	// for now just boot in random stuff

	
}

void CombatEngine::InitCombatGrid() {
	grid = new CombatGrid(this);
	grid->SetupGrid(currentLevel);

	// init enemies
	Enemy* enemyUnit1 = new Enemy(this, 0);
	combatUnits.push_back(enemyUnit1);
	grid->AddActor(enemyUnit1);
	// init players
	PlayerUnit* playerUnit1 = new PlayerUnit(this, 0);
	combatUnits.push_back(playerUnit1);
	grid->AddActor(playerUnit1);
	selectedPlayerUnit = playerUnit1;

	SortInitiative(combatUnits);
}

bool CompSpeeds(Actor* lhs, Actor* rhs) {
	return lhs->GetInitiative() > rhs->GetInitiative();
}

void CombatEngine::SortInitiative(vector<Actor*> units){
	sort(units.begin(), units.end(), CompSpeeds);
}


void CombatEngine::Update(Time t) {
	grid->Update(t);
	for (GameObject* o : combatUnits) {
		o->Update(t);
	}
	if (combatUnits[currentTurn]->GetType() == PLAYER) {
		bIsPlayerTurn = true;
	}
	else {
		bIsPlayerTurn = false;
	}
}

void CombatEngine::Draw() {
	window->clear(Color::Black);
	grid->Draw(window);
	for (GameObject* o : combatUnits) {
		o->Draw(window);
	}
	inspectPane.Draw(window);
	window->display();
}