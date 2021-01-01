#include "CombatEngine.h"


int main() {
	GAME_STATES currentState = COMBAT_SCREEN;
	RenderWindow* window = new RenderWindow(VideoMode(960, 960), "Fighting! On a grid!");
	CombatEngine* combat = new CombatEngine(window);
	while (window->isOpen()) {


		switch (currentState) {
		case MAIN_MENU:
			//MainLoop();
			break;
		case CHARACTER_SELECT:
			//CharacterSelectLoop();
			break;
		case COMBAT_SCREEN:
			combat->MainLoop();
			break;
		case REWARD_SCREEN:
			//RewardScreenLoop();
			break;

		}




	}
	return 0;
}