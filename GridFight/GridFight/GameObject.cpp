#include "GameObject.h"


GameObject::GameObject(CombatScreen* e) {
	engine = e;
	icon.setPosition(0, 0);
	type = OBJECT;
}