#include <target.h>
#include <algorithm>

bool operator< (const Target_ent &a, const Target_ent &b) {
	return (a.distance < b.distance);
}

extern "C" {

// adjust these however
const float max_tab_distance = 60.f;

struct TARGET_INTERNAL {
	uint32_t n_entries, n_allocated;
	float mvp_matrix[16];
	struct Target_ent *entities;
	pthread_mutex_t mtx;
};
static struct TARGET_INTERNAL internal;

void init_target_db() {
	internal.n_entries = 0;
	memset(internal.mvp_matrix, 0, sizeof(internal.mvp_matrix));
	internal.entities = (Target_ent*)malloc(sizeof(struct Target_ent) * 100);
	if (internal.entities) {
		internal.n_allocated = 100;
	} else internal.n_allocated = 0;
	internal.mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void reset_target_db() {
	internal.n_entries = 0;
}

void sort_target_db() {
	pthread_mutex_lock(&internal.mtx);
	std::sort(internal.entities, &internal.entities[internal.n_entries]);
	pthread_mutex_unlock(&internal.mtx);
}

// this function isn't MT safe. make sure we've finished all our mvp stuff before writing to this.
void target_db_set_mvp(const float *mvp) {
	memcpy(internal.mvp_matrix, mvp, sizeof(internal.mvp_matrix));
}

void delete_target_db() {
	free(internal.entities);
	pthread_mutex_destroy(&internal.mtx);
	internal.entities = NULL;
	internal.n_allocated = 0;
	internal.n_entries = 0;
}

struct target_entity get_next_target(const struct target_entity current, const uint8_t forward, uint8_t *restarted) {
	uint32_t pos = UINT32_MAX;
	pthread_mutex_lock(&internal.mtx);
	if (!internal.n_entries) { // nobody here fam
		pthread_mutex_unlock(&internal.mtx);
		struct target_entity out;
		out.id = NULL_PLAYER_ID;
		out.sub_id = 255;
		return out;
	}
	for (uint32_t x = 0; x < internal.n_entries; ++x) {
		// dont do this
		if (internal.entities[x].type == TARGET_TYPE_PLAYER && internal.entities[x].target.entity.id == current.id && internal.entities[x].target.entity.sub_id == current.sub_id) {
			pos = x;
			x = internal.n_entries;
		}
	}
	struct target_entity out;
	out.id = NULL_PLAYER_ID;
	out.sub_id = 255;
	// we didn't find current target in the order array, start from 0
	if (pos == UINT32_MAX) {
		for (uint32_t x = 0; x < internal.n_entries; ++x) {
			if (internal.entities[x].type == TARGET_TYPE_PLAYER && internal.entities[x].distance < max_tab_distance) {
				out = internal.entities[x].target.entity;
				x = internal.n_entries;
			}
		}
	} else {
		// we found the current target and need to start from it
		if (pos == internal.n_entries-1) {
			if (internal.entities[0].distance < max_tab_distance) {
				*restarted = true;
				out = internal.entities[0].target.entity;
			}
		} else {
			if (internal.entities[pos+1].distance < max_tab_distance) out = internal.entities[pos+1].target.entity;
		}
	}
	pthread_mutex_unlock(&internal.mtx);
	return out;
}

struct target_entity get_click_target(const int32_t x, const int32_t y) {
	target_entity out;
	out.id = NULL_PLAYER_ID;
	out.sub_id = 255;
	
	pthread_mutex_lock(&internal.mtx);
	// this is already sorted, no distance calculations required.
	for (uint32_t x = 0; x < internal.n_entries; ++x) {
		// do le maths to determine if we clicked on this
		#define MATHS 1234
		if (MATHS) {
			
			// quit this loop early
			x = internal.n_entries;
		}
	}
	
	
	pthread_mutex_unlock(&internal.mtx);
	// if we didn't find anything, we return a null player.
	return out;
}

void add_target_entry(const struct Target_ent new_ent) {
	// do le maths to determine whether or not we want this guy in here
	// ... thats mike
	
	// for now just assume we do.
	pthread_mutex_lock(&internal.mtx);
	if (internal.n_allocated == internal.n_entries) {
		const uint32_t block_resize = 100;
		// allocate more space
		Target_ent *new_ptr = (Target_ent*)malloc(sizeof(Target_ent) * (internal.n_allocated + block_resize));
		if (!new_ptr) {
			pthread_mutex_unlock(&internal.mtx);
			return; // woops we'll get you another frame buddy
		}
		memcpy(new_ptr, internal.entities, sizeof(Target_ent) * internal.n_allocated);
		free(internal.entities);
		internal.entities = new_ptr;
		internal.n_allocated += block_resize;
	}
	// append to the end of our list
	internal.entities[internal.n_entries] = new_ent;
	internal.n_entries++;

	pthread_mutex_unlock(&internal.mtx);
}

} // extern "C"