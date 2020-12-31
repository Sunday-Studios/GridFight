#include "Obstacle.h"

Obstacle::Obstacle(CombatEngine* e, int ID) : GameObject(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Tilemaps/TreeTown.png", IntRect(0, 96, 96, 96));
	icon.setTexture(texIcon);
	type = OBSTACLE;
	moveCost = 99;
}
