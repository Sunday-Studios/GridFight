#include "Obstacle.h"

Obstacle::Obstacle(GameEngine* e, int ID) : GameObject(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Tilemaps/TreeTown.png", IntRect(0, 32, 32, 32));
	icon.setTexture(texIcon);
	type = OBSTACLE;
	moveCost = 99;
}
