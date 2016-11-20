#include "spell_module.h"

#include <map>

extern "C" {

struct ext_spell_internal {
	uint16_t n_spells, max_spells;
	struct spell_entry_t *ptr;
	void **data;
	uint32_t n_data_entries;
	std::map<uint16_t, struct spell_entry_t*> internal_map;
};

static struct ext_spell_internal SPELL_INTERNAL;

void zero_spell_entry(struct spell_entry_t *s, const uint16_t id) {
	#ifdef NX_USE_ASSETS
	s->asset = NULL;
	#endif
	memset(s->path, 0, sizeof(s->path));
	s->class_id = 0;
	s->resource_cost = 0;
	s->target_type = 0;
	s->cooldown = 0;
	s->cast_time = 0;
	s->class_specific = 0;
	s->spell_tree = 0;
	s->spell_id = id;
	s->cd_until = 0;
	
	s->name = NULL;
	s->description = NULL;
	//s->description_ext = NULL;
}

// build the map
static void ext_init_spells_finish() {
	for (uint16_t x = 0; x < SPELL_INTERNAL.n_spells; ++x) {
		SPELL_INTERNAL.internal_map[SPELL_INTERNAL.ptr[x].spell_id] = &SPELL_INTERNAL.ptr[x];
	}
}

static void ext_insert_spell(const spell_entry_t spell) {
	if (SPELL_INTERNAL.n_spells < SPELL_INTERNAL.max_spells) {
		SPELL_INTERNAL.ptr[SPELL_INTERNAL.n_spells] = spell;
        SPELL_INTERNAL.ptr[SPELL_INTERNAL.n_spells].asset = nx_new_asset(spell.path, NX_IMG, NX_NON_ESSENTIAL_ASSET);
		SPELL_INTERNAL.n_spells++;
	} else {
		spell_entry_t *ptr = (spell_entry_t*)malloc(sizeof(spell_entry_t*)*(SPELL_INTERNAL.max_spells + 10));
		memcpy(ptr, SPELL_INTERNAL.ptr, sizeof(spell_entry_t*) * SPELL_INTERNAL.n_spells);
		free(SPELL_INTERNAL.ptr);
		SPELL_INTERNAL.ptr = ptr;
		SPELL_INTERNAL.max_spells += 10;
		ext_insert_spell(spell);
	}
}

static void set_path(spell_entry_t *spell, const char *path) {
	strncpy(spell->path, path, sizeof(spell->path));
}
/*
static void set_identifier(spell_entry_t *spell, const char *id) {
	
}*/

static void *new_class_data(const uint32_t n_bytes) {
	void **ptr = (void**)malloc(sizeof(void*)*(SPELL_INTERNAL.n_data_entries+1));
	void *output = malloc(n_bytes);
	memcpy(ptr, SPELL_INTERNAL.data, sizeof(void*)*(SPELL_INTERNAL.n_data_entries));
	free(SPELL_INTERNAL.data);
	SPELL_INTERNAL.data = ptr;
	SPELL_INTERNAL.data[SPELL_INTERNAL.n_data_entries] = output;
	memset(output, 0, n_bytes); 
	SPELL_INTERNAL.n_data_entries++;
	return output;
}

uint16_t ext_n_spells() {
	return SPELL_INTERNAL.n_spells;
}

struct spell_entry_t *get_spell_by_ref(const uint16_t pos) {
	if (pos > SPELL_INTERNAL.n_spells) return NULL;
	return &SPELL_INTERNAL.ptr[pos];
}

struct spell_entry_t *get_spell_by_id(const uint16_t id) {
	if (!id) return NULL;
	return SPELL_INTERNAL.internal_map[id];
}


void ext_init_spells() {
	const uint16_t initial_spell_alloc = 100;
	SPELL_INTERNAL.n_spells = 0;
	SPELL_INTERNAL.max_spells = initial_spell_alloc;
	SPELL_INTERNAL.ptr = (spell_entry_t*)malloc(sizeof(spell_entry_t)*initial_spell_alloc);
	SPELL_INTERNAL.data = NULL;
	SPELL_INTERNAL.n_data_entries = 0;
	
	spell_entry_t spell;
	// Generic spells
	zero_spell_entry(&spell, SPELL_FREEDOM);
	set_path(&spell, "resources/classes/all/icons/freedom.png");
	spell.cooldown = 12000;
	spell.target_type = TARGET_UNSPESCIFIED;
	spell.class_id = CLASS_NONE;
	ext_insert_spell(spell);
	
	zero_spell_entry(&spell, SPELL_MOUNT);
	// we need a mount icon.
	set_path(&spell, "resources/classes/all/icons/freedom.png");
	spell.cooldown = 3000;
	spell.cast_time = 2000;
	spell.class_id = CLASS_NONE;
	spell.target_type = TARGET_UNSPESCIFIED;
	ext_insert_spell(spell);
	
	// 25 rogue spells
	uint8_t pos = 0;
	spell_rogue_specific *rogue_data = (spell_rogue_specific*)new_class_data(sizeof(spell_rogue_specific) * 25);
	
	zero_spell_entry(&spell, RSPELL_KICK);
	set_path(&spell, "resources/classes/rogue/icons/kick.png");
	spell.cooldown = 10000;
	spell.target_type = TARGET_ENEMY;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_GOUGE);
	set_path(&spell, "resources/classes/rogue/icons/gouge.png");
	spell.cooldown = 10000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 45;
	spell.target_type = TARGET_ENEMY_REQUIRES_FACING;
	rogue_data[pos].combo_points_granted = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_SAP);
	set_path(&spell, "resources/classes/rogue/icons/sap.png");
	spell.cooldown = 0;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 45;
	spell.target_type = TARGET_ENEMY_OUT_OF_COMBAT;
	rogue_data[pos].requires_stealth = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_HEMO);
	set_path(&spell, "resources/classes/rogue/icons/hemorrhage.png");
	spell.cooldown = 0;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 30;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_granted = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_STEALTH);
	set_path(&spell, "resources/classes/rogue/icons/stealth.png");
	spell.cooldown = 5000;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_SELF;
	rogue_data[pos].requires_out_of_combat = 1;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_THROW);
	set_path(&spell, "resources/classes/rogue/icons/throw.png");
	spell.cooldown = 0;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_ENEMY_REQUIRES_DISTANCE;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_PREPARATION);
	set_path(&spell, "resources/classes/rogue/icons/preparation.png");
	spell.cooldown = 300000;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_SELF;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_SLICE_AND_DICE);
	set_path(&spell, "resources/classes/rogue/icons/slice_and_dice.png");
	spell.cooldown = 0;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_used = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_SPRINT);
	set_path(&spell, "resources/classes/rogue/icons/sprint.png");
	spell.cooldown = 180000;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_SELF;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_DISTRACT);
	set_path(&spell, "resources/classes/rogue/icons/distract.png");
	spell.cooldown = 25000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_ENEMY;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_VANISH);
	set_path(&spell, "resources/classes/rogue/icons/vanish.png");
	spell.cooldown = 180000;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_SELF;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_BLIND);
	set_path(&spell, "resources/classes/rogue/icons/blind.png");
	spell.cooldown = 120000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 20;
	spell.target_type = TARGET_ENEMY;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_RUPTURE);
	set_path(&spell, "resources/classes/rogue/icons/rupture.png");
	spell.cooldown = 0;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_used = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_EXPLOIT_WEAKNESS);
	set_path(&spell, "resources/classes/rogue/icons/exploit_weakness.png");
	spell.cooldown = 30000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_FRIENDLY;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_CHEAP_SHOT);
	set_path(&spell, "resources/classes/rogue/icons/cheap_shot.png");
	spell.cooldown = 0;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 40;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_granted = 2;
	rogue_data[pos].requires_stealth = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_KIDNEY_SHOT);
	set_path(&spell, "resources/classes/rogue/icons/kidney_shot.png");
	spell.cooldown = 20000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_used = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_EVASION);
	set_path(&spell, "resources/classes/rogue/icons/evasion.png");
	spell.cooldown = 120000;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_SELF;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_SHADOW_STEP);
	set_path(&spell, "resources/classes/rogue/icons/shadow_step.png");
	spell.cooldown = 25000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 10;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].no_gcd = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_GARROTE);
	set_path(&spell, "resources/classes/rogue/icons/garrote.png");
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 35;
	spell.target_type = TARGET_ENEMY_REQUIRES_BEHIND;
	rogue_data[pos].combo_points_granted = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_CLOAK);
	set_path(&spell, "resources/classes/rogue/icons/cloak.png");
	spell.cooldown = 60000;
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 10;
	spell.target_type = TARGET_SELF;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_PREMEDITATION);
	set_path(&spell, "resources/classes/rogue/icons/premeditation.png");
	spell.cooldown = 20000;
	spell.class_id = CLASS_ROGUE;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_granted = 2;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_EVISCERATE);
	set_path(&spell, "resources/classes/rogue/icons/eviscerate.png");
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 35;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_used = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_SNEAK_ATTACK);
	set_path(&spell, "resources/classes/rogue/icons/sneak_attack.png");
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 45;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_granted = 1;
	rogue_data[pos].requires_stealth = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_CRIPPLING_THROW);
	set_path(&spell, "resources/classes/rogue/icons/crippling_throw.png");
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_ENEMY_REQUIRES_DISTANCE;
	rogue_data[pos].combo_points_used = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	zero_spell_entry(&spell, RSPELL_SHIV);
	set_path(&spell, "resources/classes/rogue/icons/shiv.png");
	spell.class_id = CLASS_ROGUE;
	spell.resource_cost = 25;
	spell.target_type = TARGET_ENEMY;
	rogue_data[pos].combo_points_granted = 1;
	spell.class_specific = &rogue_data[pos];
	ext_insert_spell(spell);
	pos++;
	
	
	ext_init_spells_finish();
}


void ext_free_spells() {
	for (uint32_t x = 0; x < SPELL_INTERNAL.n_data_entries; ++x) {
		free(SPELL_INTERNAL.data[x]);
	}	
	free(SPELL_INTERNAL.data);
	free(SPELL_INTERNAL.ptr);
}

} // extern "C"
