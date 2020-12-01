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
		vector<Tile*> row;
		for (int j = 0; j < cols; j++) {
			Tile* tile = new Tile(engine, 0,i,j);
			
			tile->SetPosition(100.0f + j * 40.0f, 100.0f + i * 40.0f);
			if (j == 2 && i != 2) {
				tile->SetObstacle(0);
			}
			row.push_back(tile);
		}
		grid.push_back(row);
	}

	// enemies will be generated by gameEngine, and added
}

void CombatGrid::Draw(RenderWindow* w) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j]->Draw(w);
		}
	}
}

void CombatGrid::Update(Time t) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j]->Update(t);
		}
	}
}

void CombatGrid::AddActor(PlayerUnit* p) {
	int col = std::rand() % (cols / 2);
	int row = std::rand() % rows;
	grid[row][col]->SetActor(p);
}

void CombatGrid::AddActor(Enemy* e) {
	int col = cols - 1 - std::rand() % (cols / 2);
	int row = std::rand() % rows;
	grid[row][col]->SetActor(e);
}

Tile* CombatGrid::GetTile(Vector2i mousePos) {
	for (vector<Tile*> row : grid) {
		for (Tile* tile : row) {
			FloatRect bounds = tile->GetGlobalBounds();
			if (bounds.contains(Vector2f(mousePos))) {
				return tile;
			}
		}
	}
	return NULL;
	
}

vector<Tile*> CombatGrid::GetPath(Tile* start, Tile* end) {
	int startRow = start->GetRow();
	int startCol = start->GetCol();

	int endRow = end->GetRow();
	int endCol = end->GetCol();

	

	Path currentPath;
	vector<Path> possiblePaths;
	vector<Tile*> closedPaths;
	
	int currentCost = 9999;

	currentPath.path.push_back(start);
	possiblePaths.push_back(currentPath);
	while (possiblePaths.size() != 0) {
		currentPath = possiblePaths[0];
		possiblePaths.erase(possiblePaths.begin());
		if (currentPath.path[0] == end) {
			return currentPath.path;
		}
		if (find(closedPaths.begin(), closedPaths.end(), currentPath.path[0]) == closedPaths.end()) {
			closedPaths.push_back(currentPath.path[0]);
			
		}
		for (int i = 0; i < 4; i++) {
			
			switch (i) {
				//check above
			case 0:
				if(currentPath.path[0]->GetRow() - 1 >= 0) {
					Tile* tile = grid[currentPath.path[0]->GetRow() - 1][currentPath.path[0]->GetCol()];
					if (find(closedPaths.begin(), closedPaths.end(), tile) != closedPaths.end()) {
						cout << "Already in list" << endl;
					}
					else {
						Path path = currentPath;
						path.path.insert(path.path.begin(), tile);
						path.totalCost += tile->GetMoveCost();
						path.remainingCost = abs(endRow - tile->GetRow()) + abs(endCol - tile->GetCol());
						path.pathCost = path.totalCost + path.totalCost;
						possiblePaths = InsertPath(possiblePaths, path);
					}
				}
				break;
				//check the right
			case 1:
				if (currentPath.path[0]->GetCol() + 1 < this->cols) {
					Tile* tile = grid[currentPath.path[0]->GetRow()][currentPath.path[0]->GetCol() + 1];
					if (find(closedPaths.begin(), closedPaths.end(), tile) != closedPaths.end()) {
						cout << "Already in list" << endl;
					}
					else {
						Path path = currentPath;
						path.path.insert(path.path.begin(), tile);
						path.totalCost += tile->GetMoveCost();
						path.remainingCost = abs(endRow - tile->GetRow()) + abs(endCol - tile->GetCol());
						path.pathCost = path.totalCost + path.totalCost;
						possiblePaths = InsertPath(possiblePaths, path);
					}
				}
				break;
				//check below
			case 2:
				if (currentPath.path[0]->GetRow() + 1 < this->rows) {
					Tile* tile = grid[currentPath.path[0]->GetRow() + 1][currentPath.path[0]->GetCol()];
					if (find(closedPaths.begin(), closedPaths.end(), tile) != closedPaths.end()) {
						cout << "Already in list" << endl;
					}
					else {
						Path path = currentPath;
						path.path.insert(path.path.begin(), tile);
						path.totalCost += tile->GetMoveCost();
						path.remainingCost = abs(endRow - tile->GetRow()) + abs(endCol - tile->GetCol());
						path.pathCost = path.totalCost + path.totalCost;
						possiblePaths = InsertPath(possiblePaths, path);
					}
				}
				break;
				//check the left
			case 3:
				if (currentPath.path[0]->GetCol() - 1 >= 0) {
					Tile* tile = grid[currentPath.path[0]->GetRow()][currentPath.path[0]->GetCol() - 1];
					if (find(closedPaths.begin(), closedPaths.end(), tile) != closedPaths.end()) {
						cout << "Already in list" << endl;
					}
					else {
						Path path = currentPath;
						path.path.insert(path.path.begin(), tile);
						path.totalCost += tile->GetMoveCost();
						path.remainingCost = abs(endRow - tile->GetRow()) + abs(endCol - tile->GetCol());
						path.pathCost = path.totalCost + path.totalCost;
						possiblePaths = InsertPath(possiblePaths, path);
					}
				}
				break;
			}
		}
	}

}

int CombatGrid::GetPathCost(vector<Tile*> path) {
	int cost = 0;
	for (Tile* t : path) {
		cost += t->GetMoveCost();
	}
	return cost;
}


vector<CombatGrid::Path> CombatGrid::InsertPath(vector<Path> pathList, Path newPath) {
	int k = 0;
	while (k < pathList.size() && newPath.totalCost >= pathList[k].totalCost) {
		k++;
	}
	if (k < pathList.size()) {
		pathList.insert(pathList.begin() + k, newPath);
	}
	else {
		pathList.push_back(newPath);
	}
	return pathList;
}

