#include "GameObject.h"


GameObject::GameObject(CombatEngine* e) {
	engine = e;
	icon.setPosition(0, 0);
	type = OBJECT;
}