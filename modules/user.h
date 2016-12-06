#pragma once
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <nx_include/nx_localization.h>
#include <glm/vec3.hpp>
#include <modules/net_types.hpp>

struct Buff_entry {	
	int32_t value = 0;
	uint32_t caster_id = 0;
	uint64_t expire_time = 0;
	BUFF_ID id = 0;
};

struct health_resource_state {
	uint16_t health, resource;
	uint16_t health_max, resource_max;
};

class User;

class Entity {
private:
	char *name;

	// Movement states
	glm::vec3 position;
	float facing_angle;
	uint8_t movement_state;
	
	// Combat states
	uint16_t class_id;
	uint8_t magic_armor, physical_armor, move_speed, slow_suppression;
	health_resource_state hr_state;
	uint8_t combat_state, relationship;
	SPELL_ID currently_casting;
	
	target_entity target;
	
	std::vector<Buff_entry> buffs;
	
	User *parent;
	uint32_t id;
	
	// last_update refers to network updates only. client steps are ignored.
	uint64_t last_update;
	uint64_t last_ms_update;
public:
	Entity(User *_parent, const uint16_t _id);
	~Entity();
	void be_nice();
	
	bool is_active() const;
	void fill_data(const network_player_data &new_data);
	void update_hr_state(const health_resource_state new_state);
	
	std::vector<Buff_entry> *get_buffs();
	void clear_buffs();
	void apply_buff(const struct Buff_entry new_buff, const uint16_t buff_slot);
	
	// Advances the movement interp step by @ms milliseconds.
	void move_update(const uint32_t ms);
	void move_set(const vec3f new_pos, const float new_angle, const uint8_t new_state);
	void move_reset();
	
	glm::vec3 get_pos() const;
	
	char *get_name() const;
	health_resource_state get_hr_state() const;
};



class User {
private:
	std::unordered_map<uint8_t,Entity*> entities;
	
	PLAYER_ID player_id;
	WORLD_ID world_id;
public:
	User();
	~User();
	
	Entity *get_entity(const uint16_t id, bool *fresh = NULL);
	PLAYER_ID get_id() const;
	
	// Returns n updated as void*
	void *update_children();
	
	// Moves all children to inactive state.
	void flag_inactive();
};


// Wraps a user for threaded updates
void *update_user(void *input);
