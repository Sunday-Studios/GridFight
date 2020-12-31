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
	void SetPosition(float x, float y);
	void SetPosition(Vector2f);
	void Draw(RenderWindow* window);
	void SetEquipped(bool b) { bEquipped = b; }
protected:
	int attackDamage;
	int speedCost;
	int range;

	bool bEquipped = false;
};

