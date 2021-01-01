#pragma once
#include "Actor.h"
#include <SFML/Graphics.hpp>

class InspectPane
{
public:
	InspectPane();
	~InspectPane();
	void SetActor(Actor* a);
	void Draw(RenderWindow* w);
protected:
	Actor* actor;
	Vector2f iconPos =  Vector2f(730,30);
	Vector2f namePos = Vector2f(720,230);
	Vector2f healthPos = Vector2f(720,260);
	Vector2f speedPos = Vector2f(720,290);

	Vector2f pos = Vector2f(704, 0);

	Font font;
	Text healthText;
	Text speedText;
	Text nameText;
	bool bHasActor = false;

	Sprite icon;
	Texture texture;

	Sprite portraitBackdrop;
	Texture texBackdrop;
};

