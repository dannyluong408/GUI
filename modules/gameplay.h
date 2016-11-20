#ifndef __MODULES_GAMEPLAY_H
#define __MODULES_GAMEPLAY_H

#include <modules/game_state.h>
#include <modules/renderer.h>
#include <modules/buffs_module.h>
#include <modules/spell_module.h>
#include <modules/target.h>
#include <modules/util.h>

enum Gameplay_state {
	GAME_STATE_INIT = 0,
	GAME_STATE_CONNECTED_TCP = 1,
	GAME_STATE_CONNECTED = 2,
	GAMEPLAY_STATE_ACTIVE_1 = 3,
};

void *mylescraft_handle_gameplay(void *input);

#endif // __MODULES_GAMEPLAY_H 