#include "Tile.h"


Tile::Tile(GameEngine* e, int ID) : GameObject(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Tilemaps/TreeTown.png", IntRect(0, 0, 32, 32));
	icon.setTexture(texIcon);

	
}

void Tile::SetObstacle(int ID) {
	obstacle = new Obstacle(engine, ID);
}

void Tile::Draw(RenderWindow* w) {
	w->draw(icon);
	if (obstacle) {
		obstacle->Draw(w);
	}
}