#include "CombatGrid.h"


CombatGrid::CombatGrid(GameEngine* e) {
	engine = e;
}

CombatGrid::~CombatGrid() {

}


void CombatGrid::SetupGrid(int ID) {
	// get size of grid via generator
	// based on ID
	// default will be 6x6 board

	rows = 6; //get from generator
	cols = 5; //get from generator

	for (int i = 0; i < rows; i++) {
		vector<GameObject*> row;
		for (int j = 0; j < cols; j++) {
			Tile* tile = new Tile(engine, 0);
			tile->SetPosition(100.0f + j * 40.0f, 100.0f + i * 40.0f);
			row.push_back(tile);
		}
		grid.push_back(row);
	}

	//generate enemies too
}

void CombatGrid::Draw(RenderWindow* w) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j]->Draw(w);
		}
	}
}