#ifndef __TARGET_H
#define __TARGET_H

#include <stdint.h>
#include <net_types.hpp>
#include <pthread.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	TARGET_TYPE_PLAYER
};

union Target_ent_type {
	struct target_entity entity;
	// add a doodad thing here (like mailboxes or what have you) or dont who cares
};

struct Target_ent {
	uint8_t type;
	struct vec3f position;
	float distance;
	union Target_ent_type target;
	pthread_mutex_t mtx;
};

// if forward == false, we're going in reverse (closer instead of farther)
// if *restarted is set to true, that means we reached the end of our list and restarted.
// if we want friendly targets or a specific type of target, this function can be repeated until *repeat == true.
struct target_entity get_next_target(const struct target_entity current, const uint8_t forward, uint8_t *restarted);
struct target_entity get_click_target(const int32_t x, const int32_t y);
void target_db_set_mvp(const float *mvp);
void add_target_entry(const struct Target_ent new_ent);
void reset_target_db();
void sort_target_db();
void init_target_db();
void delete_target_db();


#ifdef __cplusplus
} // extern "C"
#endif


#endif