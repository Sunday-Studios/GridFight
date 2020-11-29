#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"

using namespace sf;
class GameEngine;

class GameObject
{
public:
	GameObject(GameEngine* e);
	~GameObject() {};
	virtual void Update(Time t) {};
	virtual void Draw(RenderWindow* window) { window->draw(icon); }
	Vector2f GetPosition() { return pos; }
	void SetPosition(float x, float y) {
		pos = Vector2f(x, y); 
		icon.setPosition(x, y);
	}
	void SetPosition(Vector2f p) { 
		pos = p; 
		icon.setPosition(p);
	}
	FloatRect GetGlobalBounds() { return icon.getGlobalBounds(); }
	OBJECT_TYPE GetType() { return type; }
protected:
	Sprite icon;
	Texture texIcon;
	GameEngine* engine;
	Vector2f pos = Vector2f(0, 0);
	OBJECT_TYPE type = OBJECT;
};

