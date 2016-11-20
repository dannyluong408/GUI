#include <modules/gameplay.h>

static void mylescraft_change_state(const uint32_t new_state) {
	static const char **str = { "GAMEPLAY_STATE_INIT", "GAMEPLAY_STATE_CONNECTED_TCP", "GAMEPLAY_STATE_CONNECTED", "GAMEPLAY_STATE_ACTIVE_1" };
	log_error("Switching game state to %s.",4,str[new_state]);
}

void *mylescraft_handle_gameplay(void *input) {
	
	ext_init_buffs();
	ext_init_spells();
	
	
	while (!game_state.quit()) {
		
		
	}
	
	return NULL;
}