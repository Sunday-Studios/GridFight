#include "Enemy.h"


Enemy::Enemy(GameEngine* e, int ID) : Actor(e) {
	// read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Enemy/targetDummy.png");
	icon.setTexture(texIcon);
	type = ENEMY;

	currentHealth = 10;
	maxHealth = 10;
	speed = 1;
	initiative = 1;
	armour = 0;
	name = "Dummy";
}