#include "CombatEngine.h"


CombatEngine::CombatEngine(RenderWindow* w) {
	window = w;
	camera = window->getDefaultView();
	Init();
	inspectPane = new InspectPane();
	actionBar = new ActionBar();
	
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
		//loop for any input logic that should update during enemy turns/animations/etc 
		// i.e. hovering over units to display inspectPane details
		if (currentUnit->GetType() == ENEMY) {
			while (window->pollEvent(event)) {

				if (event.type == sf::Event::Closed) window->close();

				if (event.type == Event::MouseMoved) {
					mousePos = Vector2i(window->mapPixelToCoords(Mouse::getPosition(*window)));
					MouseMoved();
				}
			}
		}
		
		// Enemy turn
		if (currentUnit->GetType() == ENEMY && !bDoingAction){
			if (currentUnit->GetCurrentSpeed() > 0) {
				Enemy* e = (Enemy*)currentUnit;
				AITurn(e);
			}
			else {
				AdvanceTurn();
			}
		}

		// IF currently not doing an action, but we still have some actions to do:
		if (!bDoingAction && currentUnit->GetActions().size() != 0 && !bStartOfTurnWait) {
			// IF we still have speed/action Points left
			if (currentUnit->GetCurrentSpeed() > 0) {
				// Do that action
				if (currentUnit->GetActions()[0]->GetCost() <= currentUnit->GetCurrentSpeed()) {
					DoAction(currentUnit->GetActions()[0]);
				}
			}
			// Next turn please
			else {
				
				if(!bIsPlayerTurn){
					AdvanceTurn();
				}
			}
		}

		// otherwise if we're doing an action, see if we're still moving (attacks are instant atm, will be checked for attack animation when implemented)
		else if (bDoingAction) {
			if (!currentUnit->GetMoving() && !currentUnit->GetAttacking()) {
				bDoingAction = false;
			}
		}
		// if we have speed and no actions, get instructions
		if(currentUnit->GetType() == PLAYER){
			
			// wait for mouse inputs
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
		if (bIsPlayerTurn && bEndTurn) {
			AdvanceTurn();
		}
	}
	return MAIN_MENU;
}

void CombatEngine::ConvertPathToActions(Actor* currentActor) {
	vector<Action*> actionList;
	for (int i = (int)pathToTarget.size() - 1; i >= 0; i--) {
		Tile* tile = pathToTarget[i];
		if (tile->GetHasActor()) {
			if (tile->GetActor()->GetType() != currentActor->GetType()) {
				// ACTUALLY CHECK CURRENT SELECTED ATTACK OPTION (e.g. Club, gun, etc);
				Action* action = new Action(currentActor, tile->GetActor(), ATTACK);
				actionList.push_back(action);
			}
		}
		else {
			Action* action = new Action(currentActor, tile, MOVE);
			actionList.push_back(action);
		}

	}
	currentActor->SetActions(actionList);


}

void CombatEngine::AITurn(Enemy* enemy) {
	if (enemy->GetHasTarget() == false) {
		enemy->SetTarget(playerUnits[0]);
	}
	else {
		Tile* targetTile = grid->GetTile(enemy->GetTarget());
		pathToTarget = grid->GetMeleePath(enemy->GetTile(), targetTile);
		pathToTarget.pop_back();
		ConvertPathToActions(combatUnits[currentTurn]);
	}
}

void CombatEngine::DoAction(Action* action) {
	bDoingAction = true;
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
		ACTION_BAR_RESPONSE response = actionBar->OnClick(mousePos);
		//check if clicked "end turn" button, then end turn;
		// for now just end the turn
		if (response == END_TURN) {
			bEndTurn = true;
		}
	}
	else if (Mouse::isButtonPressed(Mouse::Button::Right) && bIsPlayerTurn) {
		bStartOfTurnWait = false;
		targetTile = grid->GetTile(mousePos);
		if (targetTile != NULL) {
			for (Tile* t : pathToTarget) {
				t->SetHighlighted(false);
			}


			if (selectedPlayerUnit->GetWeapon()->GetType() == RANGED && targetTile->GetHasActor() && targetTile->GetActor()->GetType() == ENEMY) {

				vector<Action*> actionList;
				actionList.push_back(new Action(selectedPlayerUnit, targetTile->GetActor(), ATTACK));
				selectedPlayerUnit->SetActions(actionList);
				pathToTarget.clear();

			}
			else {
				pathToTarget.clear();
				pathToTarget = grid->GetMeleePath(selectedPlayerUnit->GetTile(), targetTile);
				pathToTarget.pop_back();
				ConvertPathToActions(combatUnits[currentTurn]);
				
			}
			for (Tile* t : pathToTarget) {
				t->SetHighlighted(true);
			}
		}
	}
}

void CombatEngine::AdvanceTurn() {

	do { 
		currentTurn++;
		if (currentTurn == combatUnits.size()) {
			currentTurn = 0;
		}
	} while (combatUnits[currentTurn]->IsDead() == true);
	
	Actor* currentActor = combatUnits[currentTurn];
	currentActor->ResetSpeed();
	if (currentActor->GetType() == PLAYER){
		bIsPlayerTurn = true;
		bStartOfTurnWait = true;
		actionBar->SetPlayerUnit((PlayerUnit*)(currentActor));
	}
	else {
		bIsPlayerTurn = false;
		bStartOfTurnWait = false;

	}
	bEndTurn = false;
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
			inspectPane->SetActor(highlightActor);
		}
	}
	actionBar->MouseMoved(mousePos);
	
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

	enemyUnits.push_back(enemyUnit1);
	playerUnits.push_back(playerUnit1);

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
	int enemyDeadCount = 0;
	for (int i = 0; i < combatUnits.size(); i++) {
		
		if (combatUnits[i]->IsDead()) {
			enemyDeadCount++;
		}
	}
	if (enemyDeadCount == combatUnits.size()) {
		//VICTORY!;
	}
	for (int i = 0; i < enemyUnits.size(); i++) {
		if (enemyUnits[i]->IsDead()) {
			enemyUnits.erase(enemyUnits.begin() + i);
		}
	}
	for (int i = 0; i < playerUnits.size(); i++) {
		if (playerUnits[i]->IsDead()) {
			playerUnits.erase(playerUnits.begin() + i);
		}
	}

}

void CombatEngine::Draw() {
	window->clear(Color::Black);
	grid->Draw(window);
	for (Actor* o : combatUnits) {
		if(!o->IsDead()) o->Draw(window);
	}
	inspectPane->Draw(window);
	actionBar->Draw(window);
	window->display();
}