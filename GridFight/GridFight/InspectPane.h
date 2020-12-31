#pragma once
#include "Actor.h"
#include <SFML/Graphics.hpp>

static class InspectPane
{
public:
	void SetActor(Actor* a);
	void Draw(RenderWindow* w);
protected:
	Actor* actor;
	Vector2f iconPos =  Vector2f(600,100);
	Vector2f namePos = Vector2f(600,230);
	Vector2f healthPos = Vector2f(600,260);
	Vector2f speedPos = Vector2f(600,290);


	Font font;
	Text healthText;
	Text speedText;
	Text nameText;
	bool bHasActor = false;
};

