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

	texEndTurn.loadFromFile("Textures/GUI/EndTurnButton.png");
	endTurnButton.setTexture(texEndTurn);
	endTurnButton.setPosition(710, 840);

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
	if (bHoverEndTurn) {
		w->draw(endTurnButton,&shadeEquipped);
	}
	else {
		w->draw(endTurnButton, &shadeUnEquipped);
	}
}


void ActionBar::updateWeaponSlots() {
	weapons = playerUnit->GetWeapons();
	for (int i = 0; i < weapons.size(); i++) {
		weapons[i]->SetPosition(weaponRowPositions[i]);
	}
}

ACTION_BAR_RESPONSE ActionBar::OnClick(Vector2i MousePos) {
	for (int i = 0; i < weaponSlots;i++) {
		FloatRect bounds = weaponBackings[i].getGlobalBounds();
		if (bounds.contains(Vector2f(MousePos))) {
			playerUnit->SetWeapon(i);
			currentWeapon = i;
		}
	}
	FloatRect endTurnBounds = endTurnButton.getGlobalBounds();
	if (endTurnBounds.contains(Vector2f(MousePos))) {
		return END_TURN;
	}
}

void ActionBar::MouseMoved(Vector2i MousePos) {
	FloatRect endTurnBounds = endTurnButton.getGlobalBounds();
	if (endTurnBounds.contains(Vector2f(MousePos))) {
		bHoverEndTurn = true;
	}
	else {
		bHoverEndTurn = false;
	}
}