/* CPP module to link to the game. 
	If this gets too big, we should consider transitioning to a DLL to shrink the binary a bit.
*/
#include "buffs_module.h"
#include <unordered_map>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Internal buff map */
static std::unordered_map <uint16_t, struct buff_info_t> buff_data;

void zero_buff(struct buff_info_t *b) {
	b->mod_movement_speed = 0;
	
	b->mod_damage_composite_base = 0;
	b->mod_damage_physical_base = 0;
	b->mod_damage_magical_base = 0;
	
	b->mod_damage_all = 0;
	b->mod_damage_composite = 0;
	b->mod_damage_physical = 0;
	b->mod_damage_magical = 0;
	
	b->mod_attack_speed = 0;
	
	b->mod_i_damage_composite_base = 0; 
	b->mod_i_damage_physical_base = 0; 
	b->mod_i_damage_magical_base = 0;
	b->mod_i_damage_all = 0; 
	b->mod_i_damage_composite = 0; 
	b->mod_i_damage_physical = 0;
	b->mod_i_damage_magical = 0;

	b->diminishing_return_id = 0;
	
	b->flags = 0;
	memset(b->path, 0, sizeof(b->path));
	memset(b->identifier, 0, sizeof(b->identifier));
	b->name_string = NULL;
	b->detail_string = NULL;
	
	#ifdef NX_USE_ASSETS
	b->asset = NULL;
	#endif
}

static inline void set_path(struct buff_info_t *b, const char *path) {
	const uint32_t len = strlen(path);
	assert(len < sizeof(b->path)); 
	strcpy(b->path, path);
	#ifdef NX_USE_ASSETS
	// super low priority tbh fam
    b->asset = nx_new_asset(path, NX_IMG, 255);
	#endif
}

static inline void set_identifier(struct buff_info_t *b, const char *id_name) {
	const uint32_t len = strlen(id_name);
	assert(len < sizeof(b->identifier));
	strcpy(b->identifier, id_name);
}

void add_buff_modifiers(struct buff_info_t *output, const struct buff_info_t *input) {
	output->mod_i_damage_composite_base += input->mod_i_damage_composite_base;
	output->mod_i_damage_physical_base += input->mod_i_damage_physical_base;
	output->mod_i_damage_magical_base += input->mod_i_damage_magical_base;
	output->mod_i_damage_all += input->mod_i_damage_all;
	output->mod_i_damage_composite += input->mod_i_damage_composite;
	output->mod_i_damage_physical += input->mod_i_damage_physical;
	output->mod_i_damage_magical += input->mod_i_damage_magical;
}

void ext_init_buffs() {
	/* This is probably going to end up fairly messy in the future. */
	struct buff_info_t buff;
	
	// misc DR debuffs
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_incapacitate.png");
	set_identifier(&buff, "dr_incapacitate");
	buff_data[BUFF_DR_INCAPACITATE] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_stun.png");
	set_identifier(&buff, "dr_stun");
	buff_data[BUFF_DR_STUN] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_opener_stun.png");
	set_identifier(&buff, "dr_stun_opener");
	buff_data[BUFF_DR_OPENER_STUN] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_fear.png");
	set_identifier(&buff, "dr_fear");
	buff_data[BUFF_DR_FEAR] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_silence.png");
	set_identifier(&buff, "dr_silence");
	buff_data[BUFF_DR_SILENCE] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_immobilize.png");
	set_identifier(&buff, "dr_root");
	buff_data[BUFF_DR_IMMOBILIZE] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/all/dr_disorient.png");
	set_identifier(&buff, "dr_disorient");
	buff_data[BUFF_DR_DISORIENT] = buff;
	
	/* Rogue section */
	zero_buff(&buff);
	buff.mod_movement_speed = -40;
	buff.flags = BUFF_REMOVABLE | BUFF_REMOVED_ON_DAMAGE_NOT_ABSORB;
	set_path(&buff, "resources/classes/rogue/buffs/stealth.png");
	buff_data[RBUFF_STEALTH] = buff;
	
	zero_buff(&buff);
	buff.mod_attack_speed = 60;
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/slice.png");
	buff_data[RBUFF_SLICE_AND_DICE] = buff;	
	
	zero_buff(&buff);
	buff.mod_movement_speed = 70;
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/sprint.png");
	buff_data[RBUFF_SPRINT] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/exploit_weakness.png");
	buff_data[RBUFF_EXPLOIT_WEAKNESS_ROGUE] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/exploit_weakness.png");
	buff_data[RBUFF_EXPLOIT_WEAKNESS_ROGUE_ACTIVE] = buff;
	
	zero_buff(&buff);
	buff.mod_damage_all = 15;
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/exploit_weakness.png");
	buff_data[RBUFF_EXPLOIT_WEAKNESS_FRIEND_ACTIVE] = buff;
	
	zero_buff(&buff);
	buff.mod_movement_speed = 75;
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/shadow_step.png");
	buff_data[RBUFF_SHADOW_STEP_SPEED] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_REMOVABLE;
	buff.mod_damage_physical = 25;
	buff.mod_damage_physical_base = 250;
	set_path(&buff, "resources/classes/rogue/buffs/shadow_step.png");
	buff_data[RBUFF_SHADOW_STEP_ATTACK] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/vanish.png");
	buff_data[RBUFF_VANISH] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_INTERNAL | BUFF_REMOVED_ON_DAMAGE_NOT_ABSORB | BUFF_HELPFUL_NOT_REMOVABLE;
	buff_data[RBUFF_VANISH_INTERNAL] = buff;
	
	/* How is evasion going to work anyway? */
	zero_buff(&buff);
	buff.flags = BUFF_REMOVABLE;
	set_path(&buff, "resources/classes/rogue/buffs/evasion.png");
	buff_data[RBUFF_EVASION] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_MAGICAL_IMMUNE | BUFF_REMOVABLE;
	buff.mod_damage_magical = -2000;
	set_path(&buff, "resources/classes/rogue/buffs/cloak.png");
	buff_data[RBUFF_CLOAK] = buff;
	
	/* Rogue debuffs. */
	zero_buff(&buff);
	set_path(&buff, "resources/classes/rogue/buffs/kick.png");
	buff_data[RDEBUFF_KICKED] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_IS_DISABLE | BUFF_REMOVED_ON_DAMAGE;
	buff.diminishing_return_id = BUFF_DR_INCAPACITATE;
	set_path(&buff, "resources/classes/rogue/buffs/gouge.png");
	buff_data[RDEBUFF_GOUGE] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_IS_DISABLE | BUFF_REMOVED_ON_DAMAGE | BUFF_MOVEMENT_DISABLE ;
	buff.diminishing_return_id = BUFF_DR_INCAPACITATE;
	set_path(&buff, "resources/classes/rogue/buffs/sap.png");
	buff_data[RDEBUFF_SAP] = buff;
	
	zero_buff(&buff);
	buff.mod_i_damage_physical_base = 34;
	set_path(&buff, "resources/classes/rogue/buffs/hemorrhage.png");
	buff_data[RDEBUFF_HEMO] = buff;
	
	zero_buff(&buff);
	// we may need a new flag for this kind of disable.
	buff.flags = BUFF_IS_DISABLE | BUFF_REMOVED_ON_DAMAGE | BUFF_MOVEMENT_DISABLE; 
	buff.diminishing_return_id = BUFF_DR_DISORIENT;
	set_path(&buff, "resources/classes/rogue/buffs/blind.png");
	buff_data[RDEBUFF_BLIND] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/rogue/buffs/rupture.png");
	buff_data[RDEBUFF_RUPTURE] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_IS_DISABLE | BUFF_MOVEMENT_DISABLE ;
	buff.diminishing_return_id = BUFF_DR_OPENER_STUN;
	set_path(&buff, "resources/classes/rogue/buffs/cheap_shot.png");
	buff_data[RDEBUFF_CHEAP_SHOT] = buff;
	
	zero_buff(&buff);
	set_path(&buff, "resources/classes/rogue/buffs/garrote.png");
	buff_data[RDEBUFF_GARROTE_BLEED] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_IS_DISABLE;
	buff.diminishing_return_id = BUFF_DR_SILENCE;
	set_path(&buff, "resources/classes/rogue/buffs/garrote.png");
	buff_data[RDEBUFF_GARROTE_SILENCE] = buff;
	
	zero_buff(&buff);
	buff.mod_movement_speed = -50;
	set_path(&buff, "resources/classes/rogue/buffs/crippling_throw.png");
	buff_data[RDEBUFF_CRIPPLE] = buff;
	
	zero_buff(&buff);
	buff.mod_movement_speed = -70;
	set_path(&buff, "resources/classes/rogue/buffs/crippling_poison.png");
	buff_data[RDEBUFF_CRIPPLING_POISON] = buff;
	
	zero_buff(&buff);
	/* This is only used internally on the client. */
	buff_data[RDEBUFF_DISTRACT_INTERNAL] = buff;
	
	zero_buff(&buff);
	buff.flags = BUFF_IS_DISABLE | BUFF_MOVEMENT_DISABLE ;
	buff.diminishing_return_id = BUFF_DR_STUN;
	set_path(&buff, "resources/classes/rogue/buffs/kidney_shot.png");
	buff_data[RDEBUFF_KIDNEY_SHOT] = buff;
	// End of rogue spells.
}

void ext_get_buff(const uint16_t buff_id, buff_info_t *output) {
	*output = buff_data[buff_id];
}

void ext_buff_cleanup() {
	buff_data.clear();
}

#ifdef __cplusplus
}
#endif
