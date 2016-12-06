/* NX C++ NX_DEFERRED_PROCESSING header.
 * For worker threaded i/o and SQL calls to avoid primary thread blocking. 
 * SQL jobs must be flagged appropriately. 
 * Requires lpthread */

#ifndef __MISC_DEFERRED_PROCESSING_HPP
#define __MISC_DEFERRED_PROCESSING_HPP

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS // thank you c++
#endif
#include <stdint.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <assert.h>

#ifdef __cplusplus

void *process_handler_worker(void *input);

class Process_handler {
private:
	/* @callback is run from the primary thread when @function has finished. 
	 * Do not free either function inputs within the function. They will be freed after @callback is called. */
	struct Process_info {
		void *(*function)(void *input);
		void (*callback)(void *input);
		void *function_input, *function_output;
		bool sql_job, callback_ready, reserved;
		uint16_t priority;
	};
	Process_info **job;

	pthread_t *worker;
	pthread_cond_t cond;
	pthread_mutex_t mtx;
	uint32_t current_job, n_jobs, n_allocated, n_workers;
	uint8_t sql_reserved, free_input;
	volatile sig_atomic_t should_exit;
public:
	Process_handler();
	/* Returns zero on success. MALLOC_error_callback() is called when the program fails to allocate necessary memory.	*/
	int init(const uint32_t desired_n_workers, const bool input_handled);
	void work();
	void exec_callbacks();
	/* Required to wake & join the remaining threads. */
	void exit(); 
	/* Returns nonzero on error. Errors should be handled by freeing memory and retrying. 
	 * Priority is always UINT16_MAX or NXT_DONTSORT. These jobs are added to the end of the queue. */
	int add_job(void *(*function)(void *input), void *input, void (*callback)(void *input), const bool sql);
	/* Add a job to the queue. 0 will add the job to the front of the queue. NXT_DONTSORT will add it to the end. */
	int add_job_pri(void *(*function)(void *input), void *input, void (*callback)(void *input), const bool sql, const uint16_t priority);
	int query_remaining(const uint16_t priority_threshold);
};

extern "C" {
#endif /* __cplusplus */

#define NXT_DONTSORT 0xFFFF

/* Basic C API */

int NXT_init(const uint32_t desired_n_workers, const char input_handled);
int NXT_add_job(void *(*function)(void *input), void *input, void (*callback)(void *input), const bool sql, const uint16_t priority);
int NXT_query_remaining(const uint16_t priority_threshold);
void NXT_exec_callbacks();
void NXT_wait_priority(const uint16_t priority);
void NXT_exit();

uint32_t NXT_get_nprocs();

#ifdef __cplusplus
}
#endif

#endif /* __MISC_DEFERRED_PROCESSING_HPP */