#include "Enemy.h"


Enemy::Enemy(CombatEngine* e, int ID) : Actor(e) {
	// read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Enemy/targetDummy.png");
	icon.setTexture(texIcon);
	type = ENEMY;

	currentHealth = 10;
	maxHealth = 10;
	currentSpeed = 1;
	maxSpeed = 1;
	initiative = 1;
	armour = 0;

	weapons.push_back(new Weapon(0));
	name = "Dummy";
}