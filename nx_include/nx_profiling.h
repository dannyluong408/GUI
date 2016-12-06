/* Generic profiling functions. 
 * Depends on nx_timing.h for getting time points.
 */

#ifndef __NX_PROFILING_H
#define __NX_PROFILING_H

#ifndef __NX_TIMING_H
#include "nx_timing.h"
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct nx_timer {
	uint32_t position, samples, avg_sample;
	uint64_t *timing, ref;
	void (*set)(struct nx_timer *t);
	double (*avg_time)(struct nx_timer *t);
	void (*update)(struct nx_timer *t);
	bool first_cycle, auto_mode; /* auto_mode=false implies that we will be using 'set' for our reference time instead of 'update' setting it for us. */
};

void nx_set_time_ref(struct nx_timer *container);
void nx_update_timings(struct nx_timer *container);

/* Average the previous 'avg_sample' time entries and return the value. 
 * This function will return -1.f if the number of samples is below 'avg_sample'.
 */
double nx_get_avg_time(struct nx_timer *container);
/* Set the number of samples taken when averaging the time. */
int nx_set_avg_sample(struct nx_timer *container, const uint32_t average);

void nx_init_timer(struct nx_timer *container, const uint32_t samples);
void nx_copy_timer(struct nx_timer *destination, const struct nx_timer *source);
void nx_destroy_timer(struct nx_timer *container);

struct nx_timer nx_new_timer(const int samples);

#ifdef __cplusplus
} // extern "C"

namespace nx {
	class Timer {
	private:
		nx_timer timer;
	public:
		Timer(int samples);
		Timer();
		~Timer();
		double avg_time();
		void set_auto();
		void update();
		void disable_auto();
		int set_average(uint32_t average);
		uint32_t get_num_samples();
		uint32_t get_current_samples();
		uint32_t get_avg_samples();
	};
} // namespace nx
#endif


#endif /* __NX_PROFILING_H */
