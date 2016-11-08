#include <nx_timing.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __WIN32
#include <Windows.h>
uint64_t nx_get_highres_time_us() {
	LARGE_INTEGER freq;
	LARGE_INTEGER time;
	/* This function will need to be modified to run on pre-winxp machines, or not. */
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&time); 
	return (time.QuadPart * 1000000.0 / freq.QuadPart);
}
#elif defined (__linux__)
#include <unistd.h>
#include <sys/sysinfo.h> 
#include <sys/time.h>
uint64_t nx_get_highres_time_us() {
	struct timeval time;
	/* move this over to CLOCK_MONOTONIC_RAW w/ clock_gettime eventually.
	 this will require linux >2.6.28, and will give us access to the RTC
	We need to do testing to see if we have access to the RTC first. 
	 If this is being run through KVM or some vm, we usually won't. */
	gettimeofday(&time, NULL);
	uint64_t output_us = time.tv_sec * 1000000.0; /* seconds -> us */
	output_us += time.tv_usec;
	return output_us;
}
/* Untested - need a mac to test on */
#elif defined (__MACOSX__)
#include <sys/time.h>
uint64_t nx_get_highres_time_us() {
	timeval time;
	gettimeofday(&time, NULL);
	uint64_t output_us = time.tv_sec * 1000000.0; /* seconds -> us */
	output_us += time.tv_usec;
	return output_us;
}
#endif

/* Generic OS-independent functions. Requires pthreads. */
#include <pthread.h>
#include <time.h>

/* Sleep for uint64_t nanoseconds */
void nx_nsleep(const uint64_t nanoseconds) {
	struct timespec req,rem;
	if (nanoseconds > 999999999) {
		req.tv_nsec = nanoseconds%1000000000;
		req.tv_sec = (nanoseconds - req.tv_nsec) / 1000000000;
	} else {
		req.tv_sec = 0;
		req.tv_nsec = nanoseconds;
	}
	if (nanosleep(&req,&rem) == -1) {
		uint64_t ns = rem.tv_nsec + (rem.tv_sec * 1000000000);
		nx_nsleep(ns);
	}
}

/* Sleep for uint64_t microseconds */
void nx_usleep(const uint64_t microseconds) {
	nx_nsleep(1000 * microseconds);
}

/* Sleep for uint64_t milliseconds */
void nx_msleep(const uint64_t milliseconds) {
	nx_nsleep(1000 * 1000 * milliseconds);
}

#ifdef __cplusplus
}
#endif
