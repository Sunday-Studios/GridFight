#include "Actor.h"
#include "Tile.h"
#include "Action.h"

Actor::Actor(GameEngine* e) : GameObject(e) {
	type = ACTOR;
}


void Actor::Update(Time t) {
	if (bIsMoving) {
		float xdir = moveTarget->GetPosition().x - pos.x;
		if (xdir != 0) {
			xdir = xdir / abs(xdir);
		}

		float ydir = moveTarget->GetPosition().y - pos.y;
		if (ydir != 0) {
			ydir = ydir / abs(ydir);
		}
		float elapsed = t.asSeconds();
		cout << elapsed << endl;
		SetPosition(pos.x + xdir * moveSpeed * elapsed, pos.y + ydir * moveSpeed * elapsed);
		if (abs(pos.x - moveTarget->GetPosition().x) <= 1 && abs(pos.y - moveTarget->GetPosition().y) <=1) {
			bIsMoving = false;
			SetTile(moveTarget);
			currentSpeed -= actionList[0]->GetCost();
			actionList.erase(actionList.begin());
			
		}
	}
}