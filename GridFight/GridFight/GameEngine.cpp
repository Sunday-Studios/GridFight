#include "GameEngine.h"


GameEngine::GameEngine() {
	window = new RenderWindow(VideoMode(960, 960), "Fighting! On a grid!");
	camera = window->getDefaultView();
	
}

GameEngine::~GameEngine() {

}


void GameEngine::MainLoop() {
	CreateLevel();
	InitCombatGrid();
	currentState = COMBAT_SCREEN;
	while (window->isOpen()) {
		window->setView(camera);
		Time elapsed = clock.restart();

		switch (currentState) {
		case MAIN_MENU:
			MainLoop();
			break;
		case CHARACTER_SELECT:
			CharacterSelectLoop();
			break;
		case COMBAT_SCREEN:
			CombatLoop();
			break;
		case REWARD_SCREEN:
			RewardScreenLoop();
			break;

		}

		Update(elapsed);
		Draw();

	}
	
}

GAME_STATES GameEngine::MainMenuLoop() {
	return MAIN_MENU;
}

GAME_STATES GameEngine::CharacterSelectLoop() {
	return MAIN_MENU;
}

GAME_STATES GameEngine::CombatLoop() {
	Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) window->close();

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

	}
	return MAIN_MENU;
}

GAME_STATES GameEngine::RewardScreenLoop() {
	return MAIN_MENU;
}

void GameEngine::MouseClicked() {
	if (Mouse::isButtonPressed(Mouse::Button::Left)) {
		targetTile = grid->GetTile(mousePos);
		if (targetTile->GetHasActor()) {
			Actor* actor = targetTile->GetActor();
			if (actor->GetType() == PLAYER) {
				selectedPlayerUnit = (PlayerUnit*)actor;
			}
		}

	}
	else if (Mouse::isButtonPressed(Mouse::Button::Right)) {
		targetTile = grid->GetTile(mousePos);
	}
	Actor* currentActor = combatUnits[currentTurn];
	std::cout << "unit:" <<  currentActor->GetName() << ",health: " << currentActor->GetCurrentHealth() << "/" << currentActor->GetMaxHealth() << ",speed: " << currentActor->GetSpeed() << endl;;
	currentTurn++;
	if (currentTurn == combatUnits.size()) {
		currentTurn = 0;
	}
}

void GameEngine::MouseReleased() {
	// do whatever action is queued? might need to think about logic
}

void GameEngine::MouseMoved() {
	targetTile = grid->GetTile(mousePos);
	Actor* actor = targetTile->GetActor();
	if (actor) {
		highlightActor = actor;
	}
}

void GameEngine::CreateLevel() {
	// load a level's details
	// for now just boot in random stuff

	
}

void GameEngine::InitCombatGrid() {
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

void GameEngine::SortInitiative(vector<Actor*> units){
	sort(units.begin(), units.end(), CompSpeeds);
}


void GameEngine::Update(Time t) {

}

void GameEngine::Draw() {
	window->clear(Color::Black);
	grid->Draw(window);
	for (GameObject* o : combatUnits) {
		o->Draw(window);
	}
	
	window->display();
}