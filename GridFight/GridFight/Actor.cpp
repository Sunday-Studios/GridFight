#include "Actor.h"
#include "Tile.h"
#include "Action.h"

Actor::Actor(CombatEngine* e) : GameObject(e) {
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
			
			tile->ClearActor();
			SetTile(moveTarget);
			tile->SetActor(this);
			tile->SetHighlighted(false);
			currentSpeed -= actionList[0]->GetCost();
			actionList.erase(actionList.begin());
			
		}
	}
	if (bIsAttacking) {
		//animation timer
		Action * action = actionList[0];
		Weapon* w = action->GetUser()->GetWeapon();
		action->GetTarget()->Damage(w->GetAttack());
		cout << "attack!" << endl;
		currentSpeed -= actionList[0]->GetCost();

		actionList.erase(actionList.begin());
		bIsAttacking = false;
		// start attack animation somehow
	}
	if (bHasIdleAnimation) {
		idleAnimationTimer += t.asSeconds();
		if (idleAnimationTimer >= idleAnimationRate) {
			Animate();
			idleAnimationTimer = 0;
		}
	}
}


Actor::Actor(Actor* a) {
	engine = a->engine;
	type = a->type;
	icon = a->icon;
	currentHealth = a->currentHealth;
	maxHealth = a->maxHealth;
	currentSpeed = a->currentSpeed;
	maxSpeed = a->maxSpeed;
	armour = a->armour;
	initiative = a->initiative;
	name = a->name;
}

void Actor::Damage(int damage) {
	currentHealth -= damage;
	if (currentHealth <= 0) {
		currentHealth = 0;
		bIsDead = true;
		// they are DEAD
	}
}

void Actor::Animate() {
	//CHECK IF IDLE VIA ENUM??
	currentIdleFrame++;
	if (currentIdleFrame >= idleAnimationFrames) {
		currentIdleFrame = 0;
	}
	icon.setTexture(idleAnimationFrameSet[currentIdleFrame]);
}