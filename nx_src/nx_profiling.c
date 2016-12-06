#include <nx_include/nx_profiling.h>

#ifdef __cplusplus
extern "C" {
#endif

void nx_set_time_ref(struct nx_timer *container) {
	container->ref = nx_get_highres_time_us();
}
	
void nx_update_timings(struct nx_timer *container) {
	container->timing[container->position] = nx_get_highres_time_us() - container->ref;
	if (container->auto_mode) container->ref = nx_get_highres_time_us();
	container->position++;
	if (container->position == container->samples) {
		container->first_cycle = false;
		container->position = 0;
	}
}

/* Average the previous 'avg_sample' time entries and return the value. 
 * This function will return -1.f if the number of samples is below 'avg_sample'.
 */
double nx_get_avg_time(struct nx_timer *container) {
	double return_value = -1.f;
	if (!container->first_cycle || container->position > container->avg_sample) {
		uint64_t total = 0;
		uint32_t x;
		
		int rem = container->avg_sample;
		for (x = container->position; x > 0 && rem > 0; --x,--rem) {
			total += container->timing[x];
		}
		for (x = container->samples - 1; rem > 0; --x,--rem) {
			total += container->timing[x];
		}
		return_value = (double)total/((double)container->avg_sample);
	}
	return return_value;
}
/* Set the number of samples taken when averaging the time. */
int nx_set_avg_sample(struct nx_timer *container, const uint32_t average) {
	if (average > container->samples || !average) return -1;
	else {
		container->avg_sample = average;
		return 0;
	}
}

void nx_init_timer(struct nx_timer *container, const uint32_t samples) {
	container->position = 0;
	container->first_cycle = true;
	container->auto_mode = true;
	
	if (!samples) container->samples = 100;
	else container->samples = samples;
	container->avg_sample = container->samples;
	
	container->set = &nx_set_time_ref;
	container->update = nx_update_timings;
	container->avg_time = &nx_get_avg_time;
	
#ifdef __cplusplus
	container->timing = (uint64_t*)malloc(sizeof(uint64_t) * samples);
#else
	container->timing = malloc(sizeof(uint64_t) * samples);
#endif
}
void nx_copy_timer(struct nx_timer *destination, const struct nx_timer *source) {
    nx_init_timer(destination, source->samples);
    destination->position = source->position;
    destination->first_cycle = source->first_cycle;
    destination->auto_mode = source->auto_mode;
    destination->ref = source->ref;
    memcpy(destination->timing,source->timing,sizeof(uint64_t)*source->samples);
}   
void nx_destroy_timer(struct nx_timer *container) {
	free(container->timing);
}

struct nx_timer nx_new_timer(const int samples) {
	struct nx_timer t;
	nx_init_timer(&t, samples);
	return t;
}

#ifdef __cplusplus
} // extern "C"


Timer::Timer(int samples) {
	timer = nx_new_timer(samples);
}
Timer::Timer() { 
	Timer(100); /* Default 100 samples */
} 
Timer::~Timer() {
	nx_destroy_timer(&timer);
}
double Timer::avg_time() {
	return timer.avg_time(&timer);
}
void Timer::set_auto() {
	timer.auto_mode = true;
}
void Timer::update() {
	nx_update_timings(&timer);
}
void Timer::disable_auto() {
	timer.auto_mode = false;
}
int Timer::set_average(uint32_t average) {
	return nx_set_avg_sample(&timer,average);
}
uint32_t Timer::get_num_samples() {
	return timer.samples;
}
uint32_t Timer::get_current_samples() {
	if (timer.first_cycle) return timer.position;
	else return timer.samples;
}
uint32_t Timer::get_avg_samples() {
	return timer.avg_sample;
}

} // namespace nx
#endif
