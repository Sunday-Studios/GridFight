#pragma once
#include "Actor.h"
class PlayerUnit :	public Actor
{
public:
	PlayerUnit(CombatScreen* e, int ID);
	~PlayerUnit() {};
	void Draw(RenderWindow* window);
	vector<Weapon*> GetWeapons() { return weapons; }
	int GetCurrentWeapon() { return currentWeapon; }
protected:
	void UpdateWeaponList();
	void SetEquippedWeapon(int weaponID);
};

