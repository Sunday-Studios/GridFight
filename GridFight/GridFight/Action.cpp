#include "Action.h"

Action::Action(Actor* u, Actor* ta, ACTION_TYPE ty) {
	user = u;
	target = ta;
	type = ty;

}



Action::Action(Actor* u, ACTION_TYPE ty) {
	user = u;
	type = ty;
	
}


Action::Action(Actor* u, Tile* t, ACTION_TYPE ty) {
	user = u;
	tile = t;
	type = ty;
}