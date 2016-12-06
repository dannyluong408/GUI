#include <nx_particle_system.hpp>

extern "C" {

#define BUFF_INCREMENT 100

static nx_particle_journal internal;

bool operator< (const nx_particle &a, const nx_particle &b) {
	// calculate screen distance
	float a_distance, b_distance;
	
	// get mvp matrix out of internal (well put it in first)
	
	return true;
	return (a_distance < b_distance);
}


void nx_init_particle_system() {
	internal.mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	internal.n_particles = 0;
	internal.n_allocated = 0;
	internal.particles = NULL;
}

void nx_free_particle_system() {
	pthread_mutex_destroy(&internal.mtx);
	free(internal.particles);
	internal.particles = NULL;
	internal.n_allocated = 0;
	internal.n_particles = 0;
}

int nx_new_particle(int *(*particle_function)(struct nx_particle *input, const uint64_t delta_t), void *input_data, struct nx_asset *texture, const struct vec3f position) {
	assert(particle_function);
	assert(texture);
	// This particle would never disappear without a function.
	if (!particle_function) return -1;
	if (!texture) return -1;
	
	pthread_mutex_lock(&internal.mtx);
	if (internal.n_allocated == internal.n_particles) {
		const uint32_t newsize = sizeof(nx_particle) * (internal.n_allocated + BUFF_INCREMENT)
		nx_particle *new_arr = (nx_particle*)malloc(newsize);
		if (!new_arr) {
			pthread_mutex_unlock(&internal.mtx);
			nx_log_msg("nx_new_particle: Failed to allocate %u bytes for particle buffer.",2,newsize);
			return -1;
		}
		memcpy(new_arr, internal.particles, sizeof(nx_particle) * internal.n_allocated);
		free(internal.particles);
		internal.particles = new_arr;
		internal.n_allocated += BUFF_INCREMENT;
	}
	internal.particle[internal.n_particles].update = particle_function;
	internal.particle[internal.n_particles].data = data;
	internal.particle[internal.n_particles].tex = texture;
	internal.particle[internal.n_particles].position = position;
	pthread_mutex_unlock(&internal.mtx);
	return 0;
}

void update_particles(const uint64_t delta_t) {
	pthread_mutex_lock(&internal.mtx);
	for (uint32_t x = 0; x < internal.n_particles; ++x) {
		const int ret = internal.particle[x].update(&internal.particle[x], delta_t);
		// ret == 0 means the particle has finished.
		if (!ret) {
			internal.particle[x] = internal.particle[internal.n_particles-1];
			x--;
			internal.n_particles--;
		}
	}
	pthread_mutex_unlock(&internal.mtx);
}

int nx_cp_particle_journal(struct nx_particle_journal *out) {
	pthread_mutex_lock(&internal.mtx);
	const uint32_t newsize = sizeof(nx_particle) * internal.n_particles;
	nx_particle *alloc = (nx_particle*)malloc(newsize);
	if (!new_arr) {
		pthread_mutex_unlock(&internal.mtx);
		nx_log_msg("nx_cp_particle_journal: Failed to allocate %u bytes for new particle journal.",2,newsize);
		return -1;
	}
	
}

} // extern "C"