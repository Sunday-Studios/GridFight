#include "CombatScreen.h"
#include "MainScreen.h"
#include "RewardScreen.h"

int main() {
	GAME_STATES currentState = COMBAT_SCREEN;
	RenderWindow* window = new RenderWindow(VideoMode(960, 960), "Fighting! On a grid!");
	MainScreen* mainMenu;
	CombatScreen* combat = new CombatScreen(window);
	RewardScreen* reward;
	COMBAT_STATES combatState;
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
			combatState = combat->GetState();
			switch (combatState) {
			case FIGHTING:
				break;
			case END_LOSE:
				cout << "YOU LOSE!" << endl;
				break;
			case END_WIN:
				cout << "YOU WIN!" << endl;
				
				break;
			}
			break;
		case REWARD_SCREEN:
			//RewardScreenLoop();
			break;

		}




	}
	return 0;
}