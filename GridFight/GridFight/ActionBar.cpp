#include "ActionBar.h"

ActionBar::ActionBar() {
	texture.loadFromFile("Textures/GUI/ActionBar.png");
	icon.setTexture(texture);
	icon.setPosition(posX, posY);


	texWepBack.loadFromFile("Textures/Weapons/background.png");
	for (int i = 0; i < weaponSlots; i++) {
		weaponBackings[i].setTexture(texWepBack);
		weaponBackings[i].setPosition(weaponRowPositions[i]);
	}

	shadeEquipped.loadFromFile("Textures/Shaders/Equipped.vert", Shader::Vertex);
	shadeUnEquipped.loadFromFile("Textures/Shaders/unEquipped.vert", Shader::Vertex);

}


void ActionBar::Draw(RenderWindow* w) {
	w->draw(icon);
	for (int i = 0; i < weaponSlots; i++) {
		if (i == currentWeapon) {
			w->draw(weaponBackings[i],&shadeEquipped);
		}
		else {
			w->draw(weaponBackings[i], &shadeUnEquipped);
		}
	}
	for (int i = 0; i < weapons.size(); i++) {
		weapons[i]->Draw(w);
	}
}


void ActionBar::updateWeaponSlots() {
	weapons = playerUnit->GetWeapons();
	for (int i = 0; i < weapons.size(); i++) {
		weapons[i]->SetPosition(weaponRowPositions[i]);
	}
}