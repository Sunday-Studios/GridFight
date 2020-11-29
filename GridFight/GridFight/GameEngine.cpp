#include "GameEngine.h"


GameEngine::GameEngine() {
	window = new RenderWindow(VideoMode(960, 960), "Fighting! On a grid!");
	camera = window->getDefaultView();
	
}

GameEngine::~GameEngine() {

}


void GameEngine::MainLoop() {
	while (window->isOpen()) {
		window->setView(camera);
		Time elapsed = clock.restart();
		Event event;

		Update(elapsed);
		CreateLevel();
		InitCombatGrid();
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

		}



		Draw();

	}
	
}

void GameEngine::MouseClicked() {
	if (Mouse::isButtonPressed(Mouse::Button::Left)) {

	}
	else if (Mouse::isButtonPressed(Mouse::Button::Right)) {
	
	}
}

void GameEngine::MouseReleased() {
	// do whatever action is queued? might need to think about logic
}

void GameEngine::CreateLevel() {
	// load a level's details
	// for now just boot in random stuff

	Tile* background = new Tile(this,0);
	Actor* playerUnit1 = new PlayerUnit(this,0);
	Actor* enemyUnit1 = new Enemy(this,0);

	gameObjects.push_back(background);
	background->SetObstacle(0);
	gameObjects.push_back(playerUnit1);
	gameObjects.push_back(enemyUnit1);
}

void GameEngine::InitCombatGrid() {
	grid = new CombatGrid(this);
	grid->SetupGrid(0);
}

void GameEngine::Update(Time t) {

}

void GameEngine::Draw() {
	window->clear(Color::Black);
	for (GameObject* o : gameObjects) {
		o->Draw(window);
	}
	grid->Draw(window);
	window->display();
}