/* Generic portable timing utilities
 * All functions are prefixed with nx_
 * 
 * Sleep functions require pthread library.
 */
#ifndef __NX_TIMING_H
#define __NX_TIMING_H

#include <stdint.h>
#include <pthread.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t nx_get_highres_time_us();
void nx_nsleep(const uint64_t nanoseconds);
void nx_usleep(const uint64_t microseconds);
void nx_msleep(const uint64_t milliseconds);

#ifdef __cplusplus
}
#endif
#endif // __NX_TIMING_H