#pragma once
#include "PlayerUnit.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class ActionBar
{
public:
	ActionBar();
	~ActionBar() {};
	void Draw(RenderWindow* w);
	void SetPlayerUnit(PlayerUnit* p) {
		playerUnit = p; 
		currentWeapon = playerUnit->GetCurrentWeapon();
		updateWeaponSlots();
	}
protected:
	int posX = 0;
	int posY = 960 - 256;
	int weaponSlots = 3;
	Vector2f weaponRowPositions[3] = { Vector2f(60, 730), Vector2f(170, 730),Vector2f(280, 730) };

	Sprite icon;
	Texture texture;

	Sprite weaponBackings[3];
	Texture texWepBack;

	vector<Weapon*> weapons;

	Shader shadeEquipped;
	Shader shadeUnEquipped;

	PlayerUnit* playerUnit;
	void updateWeaponSlots();
	int currentWeapon = 0;
};

