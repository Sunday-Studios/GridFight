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
	ACTION_BAR_RESPONSE OnClick(Vector2i MousePos);
	void MouseMoved(Vector2i MousePos);
protected:
	float posX = 0.f;
	float posY = 704.f;
	int weaponSlots = 3;
	Vector2f weaponRowPositions[3] = { Vector2f(60, 730), Vector2f(170, 730),Vector2f(280, 730) };

	Sprite icon;
	Texture texture;

	Sprite weaponBackings[3];
	Texture texWepBack;

	Sprite endTurnButton;
	Texture texEndTurn;

	vector<Weapon*> weapons;

	Shader shadeEquipped;
	Shader shadeUnEquipped;

	PlayerUnit* playerUnit;
	void updateWeaponSlots();
	int currentWeapon = 0;

	bool bHoverEndTurn = false;
};

