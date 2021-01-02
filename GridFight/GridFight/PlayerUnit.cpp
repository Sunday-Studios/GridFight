#include "PlayerUnit.h"


PlayerUnit::PlayerUnit(CombatScreen* e, int ID) : Actor(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);

	//int frames = READ_FROM_FILE;
	idleAnimationFrames = 4;
	bHasIdleAnimation = true;
	for (int i = 0; i < idleAnimationFrames; i++) {
		Texture tex;
		tex.loadFromFile("Textures/Player/Heroes/Axeman.png", IntRect(96*i,0,96,96));
		idleAnimationFrameSet.push_back(tex);
	}
	

	//texIcon.loadFromFile("Textures/Player/Player.png");
	icon.setTexture(idleAnimationFrameSet[currentIdleFrame]);
	type = PLAYER;

	maxHealth = 40;
	currentHealth = 40;
	currentSpeed = 3;
	maxSpeed = 3;
	initiative = 3;
	armour = 0;
	name = "Hero";
	weapons.push_back(new Weapon(0));
	weapons.push_back(new Weapon(1));
	SetEquippedWeapon(0);
	

	UpdateWeaponList();

}

void PlayerUnit::UpdateWeaponList() {
	for (int i = 0; i < weapons.size();i++) {
		Weapon* wep = weapons[i];
	}
}

void PlayerUnit::Draw(RenderWindow* window){
	Actor::Draw(window);
	for (Weapon* wep : weapons) {
		wep->Draw(window);
	}
}

void PlayerUnit::SetEquippedWeapon(int weaponID) {
	currentWeapon = 0;
	weapons[currentWeapon]->SetEquipped(true);
}