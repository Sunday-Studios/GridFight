#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Tile;
using namespace sf;

class Actor : public GameObject
{
public:
	Actor(GameEngine* e);
	~Actor() {};
	virtual void Update(Time t) {}
	int GetCurrentHealth() { return currentHealth; }
	int GetMaxHealth() { return maxHealth; }
	int GetSpeed() { return speed; }
	int GetArmour() { return armour; }
	int GetInitiative() { return initiative; }
	std::string GetName() { return name; }
	Tile* GetTile() { return tile; }
	void SetTile(Tile* t) { tile = t; }
protected:
	Tile* tile;
	int currentHealth = 0;
	int maxHealth = 0;
	int speed = 0;
	int armour = 0;
	int initiative = 0;
	std::string name = "";

};

