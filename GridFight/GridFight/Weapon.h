#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Weapon : public GameObject
{
public:
	Weapon(int ID);
	~Weapon() {}
	int GetAttack() { return attackDamage; }
	int GetRange() { return range; }
	int GetCost() { return speedCost; }
protected:
	int attackDamage;
	int speedCost;
	int range;

};

