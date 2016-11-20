#ifndef __NX_PARTICLE_SYSTEM_HPP
#define __NX_PARTICLE_SYSTEM_HPP
#include <nx_asset.h>
#include <net_types.hpp>
#include <nx_error.h>

#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

struct nx_particle {
	// Function prototype for particle updates. If function returns 0, the particle is deleted.
	// @data must be freed manually by the update function.
	// Update must not run particle functions (ie. nx_new_particle)
	int *(*update)(struct nx_particle *input, const uint64_t delta_t);
	void *data;
	struct nx_asset *tex;
	struct vec3f position;
	float scale;
};

struct nx_particle_journal {
	struct nx_particle *particles;
	uint32_t n_particles, n_allocated;
	pthread_mutex_t mtx;
};


#ifdef __cplusplus
extern "C" {
#endif

void nx_init_particle_system();
void nx_free_particle_system();

// Add a particle to our journal. Returns 0 on success.
int nx_new_particle(int *(*particle_function)(struct nx_particle *input, const uint64_t delta_t), void *input_data, struct nx_asset *texture, const struct vec3f position);
void nx_update_particles(const uint64_t delta_t);

// Allocates a new, independent particle journal copy for the rendering thread.
int nx_cp_particle_journal(struct nx_particle_journal *out);

#ifdef __cplusplus
} // extern "C"
#endif
#endif // __NX_PARTICLE_SYSTEM_HPP