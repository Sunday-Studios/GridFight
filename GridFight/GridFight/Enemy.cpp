#include "Enemy.h"


Enemy::Enemy(GameEngine* e, int ID) : Actor(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Enemy/targetDummy.png");
	icon.setTexture(texIcon);
}