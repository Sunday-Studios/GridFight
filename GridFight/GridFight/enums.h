#pragma once


enum GAME_STATES {
	MAIN_MENU,
	CHARACTER_SELECT,
	COMBAT_SCREEN,
	REWARD_SCREEN
};


enum OBJECT_TYPE {
	ACTOR,
	ENEMY,
	PLAYER,
	OBJECT,
	OBSTACLE
};

enum ACTION_TYPE {
	MOVE,
	ATTACK,
	SPECIAL
};

enum ACTION_BAR_RESPONSE {
	WEAPON_SWITCH,
	ABILITY_USE,
	END_TURN
};

enum WEAPON_TYPE {
	MELEE,
	RANGED
};