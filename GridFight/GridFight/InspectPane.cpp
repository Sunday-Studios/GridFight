#include "InspectPane.h"
InspectPane::InspectPane() {
	texture.loadFromFile("Textures/GUI/InspectPane.png");
	icon.setTexture(texture);
	icon.setPosition(pos);

	texBackdrop.loadFromFile("Textures/GUI/PortraitBackdrop.png");
	portraitBackdrop.setTexture(texBackdrop);
	portraitBackdrop.setPosition(iconPos);
}

InspectPane::~InspectPane() {

}

void InspectPane::SetActor(Actor* a) {
	actor = a;
	bHasActor = true;
	font.loadFromFile("Font/Arial.ttf");
	
	healthText.setString("Health: " + to_string(actor->GetCurrentHealth()) + " / " + to_string(actor->GetMaxHealth()));
	speedText.setString("Speed: " + to_string(actor->GetCurrentSpeed()) + " / " + to_string(actor->GetMaxSpeed()));	
	nameText.setString("Name: " + actor->GetName());

	healthText.setFont(font);
	speedText.setFont(font);
	nameText.setFont(font);

	healthText.setPosition(healthPos);
	speedText.setPosition(speedPos);

	nameText.setPosition(namePos);

	actor->SetPosition(iconPos);
	actor->SetScale(2);
}

void InspectPane::Draw(RenderWindow* w) {
	w->draw(icon);
	w->draw(portraitBackdrop);
	if (bHasActor) {
		w->draw(healthText);
		w->draw(speedText);

		w->draw(nameText);
		actor->Draw(w);
	}
}