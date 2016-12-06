#include <string.h>
#include "user.h"
#include "game.h"
#include "net_types.hpp"

// REPLACE THIS WITH LOCALIZE FUNCTION
static const char *unknown_name = "Unknown";

User::User() {
	player_id = NULL_PLAYER_ID;
	world_id = NULL_WORLD_ID;
	//get_entity(0); // Initialize the player's main entity. why?
}

User::~User() {
    for (auto e : entities) {
        delete e.second;
	}
}

PLAYER_ID User::get_id() const {
	return player_id;
}

Entity *User::get_entity(const uint16_t id, bool *fresh) {
	assert(id != 0xffff); // reserved
    if (entities.find(id) == entities.end()) {
        entities[id] = new Entity(this, id);
		if (fresh) *fresh = true;
	}
	return entities[id];
}

void *User::update_children() {
	uint32_t count = 0;
    for (auto e : entities) {
        if (e.second->is_active()) {
            e.second->move_update(game.current_step());
			count++;
		}
	}
	return (void*)count;
}

void User::flag_inactive() {
	vec3f pos;
	pos.x = 0.f;
	pos.y = -10000000.f;
	pos.z = 0.f;
	for (auto e : entities) {
		e.second->move_set(pos, 0.f, 0xff);
	}
}

// Entities must be aware of their target_t identifiers.
Entity::Entity(User *_parent, const uint16_t _id) {
	parent = _parent;
	id = _id;
	
	move_reset();
    class_id = 0;
	magic_armor = 100;
	physical_armor = 100;
	move_speed = 100;
	slow_suppression = 100;
    memset((void*)&hr_state, 0, sizeof(hr_state));
	
	combat_state = 0;
	relationship = 0;
	currently_casting = 0;
	
	target.id = NULL_PLAYER_ID;
	target.sub_id = 0xffff; // Null sub-id
	
	last_update = game.now();
	last_ms_update = game.now();
	
	#ifndef NDEBUG
	game.mod_entity_count(1);
	#endif
}

Entity::~Entity() {
	free(name);	
	#ifndef NDEBUG
	game.mod_entity_count(-1);
	#endif
}

void Entity::be_nice() {
	while (!buffs.empty() && buffs.back().expire_time == 0) {
		buffs.pop_back();
	}
	buffs.shrink_to_fit();
}

bool Entity::is_active() const {
	return movement_state != 0xff;
}

void Entity::fill_data(const network_player_data &data) {
	#ifdef EFILL
	#error "EFILL already defined"
	#endif
    #define EFILL(x) x = data. x
	EFILL(class_id);
    hr_state.health = data.health;
    hr_state.health_max = data.health_max;
    hr_state.resource = data.resource;
    hr_state.resource_max = data.resource_max;
	EFILL(move_speed);
	EFILL(magic_armor);
	EFILL(physical_armor);
	EFILL(slow_suppression);
	EFILL(combat_state);
	EFILL(relationship);
	EFILL(target);
	#undef EFILL
	
	// Double check the name. It should be sanitized before being input.
	assert(data.name[sizeof(data.name)-1] == 0);
	
	size_t len = strnlen(data.name, sizeof(data.name)-1);
	name = (char*)malloc(len+1);
	memcpy(name, data.name, len);
	name[len] = 0;
}

void Entity::update_hr_state(const health_resource_state new_state) {
	hr_state = new_state;
}

// this hurts me inside
std::vector<Buff_entry> *Entity::get_buffs() {
	return &buffs;
}

void Entity::clear_buffs() {
	buffs.clear();
}

void Entity::apply_buff(const struct Buff_entry new_buff, const uint16_t buff_slot) {
	if (buffs.size() <= buff_slot) {
		buffs.resize(buff_slot);
	}
	buffs[buff_slot] = new_buff;
}

// @mike please assist 
void Entity::move_update(const uint32_t ms) {
	// check if we've updated already this step.
	if (last_ms_update != game.now()) {
		// if not, update our position here.
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
        uint32_t use_ms = ms;
    #pragma GCC diagnostic pop

		
	}
	// get camera
    //Camera the_game_camera = game.get_camera(); // this is how you get the camera.
	// determine if this entity is within our view distance
	
	
	
	// determine if this entity fits (approximately) within the game's camera
	
	
	
	// if so, queue the draw
	if (1) { 
		game.queue_draw(this);
	}
}

void Entity::move_set(const vec3f new_pos, const float new_angle, const uint8_t new_state) {
	last_update = game.now();
	position.x = new_pos.x;
	position.y = new_pos.y;
	position.z = new_pos.z;
	
	facing_angle = new_angle;
	
	movement_state = new_state;
}

void Entity::move_reset() {
	position.x = 0.f;
	// throw this person outside of any reasonable drawing position.
	position.y = -10000000.f;
	position.z = 0.f;
	movement_state = 0xff; // flag as a null movement state
}

glm::vec3 Entity::get_pos() const {
	return position;
}

char *Entity::get_name() const {
	if (name) return name;
    else return (char*)unknown_name; // hehe
}

health_resource_state Entity::get_hr_state() const {
	return hr_state;
}

void *update_user(void *input) {
	User *u = (User*)input;
	return u->update_children();
}


