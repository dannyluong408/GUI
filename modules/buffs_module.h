#ifndef __BUFFS_MODULE_H
#define __BUFFS_MODULE_H

#include <stdint.h>
#include <string.h>
#include <nx_include/spell_list.h>

#ifdef NX_USE_ASSETS
#include <nx_include/nx_asset.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct buff_info_t {
	/* Gameplay modifiers. The only value the client needs to know is mod_movement_speed. */
	int16_t mod_movement_speed, 
		/* Base damage modifiers add damage to the raw damage before multipliers. */
		mod_damage_composite_base, mod_damage_physical_base, mod_damage_magical_base, 
		/* Non-base damage modifiers additively modify damage by a percentage 
		 * EX: values of 15 and -25 will result in a net damage of 90% */
		mod_damage_all, mod_damage_composite, mod_damage_physical, mod_damage_magical,
		mod_attack_speed;
	
	/* Same deal except modifies incoming damage on the buffed target. */
	int16_t mod_i_damage_composite_base, mod_i_damage_physical_base, mod_i_damage_magical_base,
		mod_i_damage_all, mod_i_damage_composite, mod_i_damage_physical, mod_i_damage_magical;
	
	/* DR ids are identical to their buff ID. */
	uint16_t diminishing_return_id;
	
	uint8_t buff_type; 
	
	/* Type-checking bit flags. */
	uint16_t flags;
	char path[128];
	char identifier[64];
	char *name_string, *detail_string;
	
	#ifdef NX_USE_ASSETS
	struct nx_asset *asset;
	#endif
};

/* Buff bit flags */
enum {
	/* Buff is used internally only and is not transmitted to clients. */
	BUFF_INTERNAL = 1,
	/* Buff is removed by SPELL_FREEDOM and applies buff_prototype_t->diminishing_return_id DR on removal. */
	BUFF_IS_DISABLE = 2, 
	/* Buff absorbs all generic damage. Buffs with this flag must store absorb value in the value field. */
	BUFF_ABSORB_MODIFIER = 4,
	/* Buff is removed on damage. Additionally, if BUFF_IS_DISABLE is flagged, applies DR on removal. */
	BUFF_REMOVED_ON_DAMAGE = 8,
	/* Physical and magical ability immunity flags. */
	BUFF_MAGICAL_IMMUNE = 16,
	BUFF_PHYSICAL_IMMUNE = 32,
	/* The buff can be right-click removed under any circumstances. */
	BUFF_REMOVABLE = 64,
	BUFF_HELPFUL_NOT_REMOVABLE = 128,
	BUFF_REMOVED_ON_DAMAGE_NOT_ABSORB = 256,
	/* The buff disables all forms of movement incl. turning and jumping. */
	BUFF_MOVEMENT_DISABLE = 512,
	/* Turning allowed, movement not allowed */
	BUFF_MOVEMENT_ROOT = 1024,
};

void zero_buff(struct buff_info_t *b);
void add_buff_modifiers(struct buff_info_t *output, const struct buff_info_t *input);
void ext_init_buffs();
void ext_get_buff(const uint16_t buff_id, struct buff_info_t *output);
void ext_buff_cleanup();

#ifdef __cplusplus
}
#endif

#endif /* __BUFFS_HPP */
