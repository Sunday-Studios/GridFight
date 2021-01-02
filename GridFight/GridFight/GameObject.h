#pragma once
#include <SFML/Graphics.hpp>
#include "enums.h"

using namespace sf;
class CombatScreen;

class GameObject
{
public:
	GameObject(CombatScreen* e);
	GameObject() {}
	~GameObject() {};
	virtual void Update(Time t) {};
	virtual void Draw(RenderWindow* window) { window->draw(icon); }
	Vector2f GetPosition() { return pos; }
	virtual void SetPosition(float x, float y) {
		pos = Vector2f(x, y); 
		icon.setPosition(x, y);
	}
	virtual void SetPosition(Vector2f p) { 
		pos = p; 
		icon.setPosition(p);
	}
	FloatRect GetGlobalBounds() { return icon.getGlobalBounds(); }
	OBJECT_TYPE GetType() { return type; }
	void SetScale(float scale) { icon.setScale(scale, scale); }

protected:
	Sprite icon;
	Texture texIcon;
	Shader shader;
	CombatScreen* engine;
	Vector2f pos = Vector2f(0, 0);
	OBJECT_TYPE type = OBJECT;
};

