#include "Weapon.h"



Weapon::Weapon(int ID) {
	if (ID == 0) {
		texIcon.loadFromFile("Textures/Weapons/axe.png");
		range = 1;
		attackDamage = 5;
	}
	if (ID == 1) {
		texIcon.loadFromFile("Textures/Weapons/bow.png");
		range = 2;
		attackDamage = 3;
	}
	//load stats from ID in files
	icon.setTexture(texIcon);

	speedCost = 1;
}

void Weapon::SetPosition(float x, float y) {
	GameObject::SetPosition(x, y);

}


void Weapon::SetPosition(Vector2f v) {
	GameObject::SetPosition(v);

}


void Weapon::Draw(RenderWindow* window) {
	
	GameObject::Draw(window);
	
}