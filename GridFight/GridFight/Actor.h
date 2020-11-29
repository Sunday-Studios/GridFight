#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Actor : public GameObject
{
public:
	Actor(GameEngine* e);
	~Actor() {};
	virtual void Update(Time t) {}

};

