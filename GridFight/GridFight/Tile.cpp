#include "Tile.h"


Tile::Tile(CombatScreen* e, int ID, int r, int c) : GameObject(e) {
	//read ID details from text file; XML/JSON/PlainText
	// getInfo(ID, OBJECT_TYPE_ENEMY);
	texIcon.loadFromFile("Textures/Tilemaps/TreeTown.png", IntRect(0, 0, 96, 96));
	icon.setTexture(texIcon);
	row = r;
	col = c;
	shader.loadFromFile("Textures/Shaders/available.vert",Shader::Vertex);

}

void Tile::SetObstacle(int ID) {
	obstacle = new Obstacle(engine, ID);
	obstacle->SetPosition(this->GetPosition());
	bHasObstacle = true;
}

void Tile::Draw(RenderWindow* w) {
	if (bIsHighlighted) {
		w->draw(icon, &shader);
	}
	else {
		w->draw(icon);
	}
	if (bHasObstacle) {
		obstacle->Draw(w);
	}
}

void Tile::Update(Time t) {
	shader.setUniform("time", clock.getElapsedTime().asSeconds());
	if (actor) {
		if (actor->IsDead()) {
			ClearActor();
		}
	}
}

bool Tile::SetActor(Actor* a) {
	if (!actor) {
		actor = a;
		actor->SetPosition(this->GetPosition());
		actor->SetTile(this);
		bHasActor = true;
		return true;
	}
	return false;
}