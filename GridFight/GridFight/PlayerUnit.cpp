#include "PlayerUnit.h"


PlayerUnit::PlayerUnit(GameEngine* e, int ID) : Actor(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Player/Player.png");
	icon.setTexture(texIcon);
	type = PLAYER;

	maxHealth = 40;
	currentHealth = 40;
	speed = 3;
	initiative = 3;
	armour = 0;
	name = "Hero";
}