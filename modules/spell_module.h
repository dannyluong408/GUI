#ifndef __SPELL_MODULE_H
#define __SPELL_MODULE_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <nx_include/spell_list.h>

#ifdef NX_USE_ASSETS
#include <nx_include/nx_asset.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct spell_rogue_specific {
	uint8_t combo_points_granted;
	uint8_t combo_points_used;
	uint8_t requires_stealth;
	uint8_t requires_out_of_combat; // self out of combat, ie stealth
	uint8_t no_gcd;
};

struct spell_entry_t {
    char path[255];
	#ifdef NX_USE_ASSETS
	struct nx_asset *asset;
	#endif
	
	uint8_t class_id, spell_tree;
	uint16_t spell_id, resource_cost, target_type;
	// in milliseconds
	uint64_t cooldown, cast_time, cd_until;
	void *class_specific;
	
	char *name, *description, *description_alt;
};

void zero_spell_entry(struct spell_entry_t *s, const uint16_t id);
void ext_init_spells();
void ext_free_spells();
uint16_t ext_n_spells();
struct spell_entry_t *get_spell_by_ref(const uint16_t pos);
struct spell_entry_t *get_spell_by_id(const uint16_t id);
// Returns 1 on success
int ext_get_spell(const uint16_t spell_id, struct spell_entry_t *output);

#ifdef __cplusplus
}
#endif

#endif // __SPELL_MODULE_H
