#include "nx_include/nx_deferred_processing.hpp"

void *process_handler_worker(void *input) {
	Process_handler *handler = (Process_handler*)input;
	handler->work();
	return NULL;
}

Process_handler::Process_handler() {
	worker = NULL;
	job = NULL;
	current_job = 0;
	n_jobs = 0;
	n_workers = 0;
	n_allocated = 0;
	sql_reserved = false;
	should_exit = false;
	free_input = true;
}

void Process_handler::exit() {
	pthread_mutex_lock(&mtx);
	should_exit = true;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mtx);
	for (uint32_t x = 0; x < n_workers; ++x) {
		pthread_join(worker[x], NULL);
	}
	free(worker);
	worker = NULL;
	for (uint32_t x = 0; x < n_jobs; ++x) {
		free(job[x]);
	}
	free(job);
	job = NULL;
}

int Process_handler::init(uint32_t desired_n_workers, const bool input_handled) {
	free_input = !input_handled;
	if (!desired_n_workers) {
		// default 2
		desired_n_workers = 2;
	}
	worker = (pthread_t*)malloc(sizeof(pthread_t)*desired_n_workers);
	if (!worker) return -2;
	mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

	pthread_attr_t attr;
	if (pthread_attr_init(&attr)) return -4;
	if (pthread_attr_setstacksize(&attr, 8388608)) return -5;
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)) return -6;
	
	for (uint32_t x = 0; x < desired_n_workers; ++x) {
		const int error = pthread_create(&worker[x], &attr, process_handler_worker, (void*)this);
		if (error) return -7;
		else n_workers++;
	}
	return 0;
}

void Process_handler::work() {
	Process_info *assigned_job;
	bool have_sql_lock = false;
	uint32_t previous_n_jobs = 0;
	while (!should_exit) {
		pthread_mutex_lock(&mtx);
		previous_n_jobs = n_jobs;
		assigned_job = NULL;
		for (uint32_t x = 0; x < n_jobs; ++x) {
			// Find a job
			if (!job[x]->reserved) {
				// Make sure we have or can lock sql access if its an sql job
				if (job[x]->sql_job) {
					if (have_sql_lock || !sql_reserved) {
						job[x]->reserved = true;
						assigned_job = job[x];
						sql_reserved = true;
						have_sql_lock = true;
						x = n_jobs;
					}
				} else {
					job[x]->reserved = true;
					assigned_job = job[x];
					x = n_jobs;
				}
			}
			previous_n_jobs--;
		}
		pthread_mutex_unlock(&mtx);
		if (assigned_job) {
			assigned_job->function_output = assigned_job->function(assigned_job->function_input);
			assigned_job->callback_ready = 1; // must be 1
		}
		if (have_sql_lock) {
			pthread_mutex_lock(&mtx);
			sql_reserved = false;
			have_sql_lock = false;
			pthread_mutex_unlock(&mtx);
		}
		if (!previous_n_jobs) {
			pthread_mutex_lock(&mtx);
			pthread_cond_wait(&cond, &mtx);
			pthread_mutex_unlock(&mtx);
		}
	}
}

int Process_handler::add_job(void *(*function)(void *input), void *input, void (*callback)(void *input), const bool sql) {
	return add_job_pri(function, input, callback, sql, NXT_DONTSORT);
}

int Process_handler::add_job_pri(void *(*function)(void *input), void *input, void (*callback)(void *input), const bool sql, const uint16_t priority) {
	assert(function);
	Process_info *new_job = (Process_info*)malloc(sizeof(Process_info));
	if (!new_job) return -1;
	new_job->function = function;
	new_job->callback = callback;
	new_job->function_input = input;
	new_job->function_output = NULL;
	new_job->sql_job = sql;
	new_job->callback_ready = 0;
	new_job->reserved = false;
	new_job->priority = priority;
	new_job->callback_ready = false;
	
	pthread_mutex_lock(&mtx);
	if (n_jobs == n_allocated) {
		Process_info **ptr = (Process_info**)malloc(sizeof(Process_info*)*(n_allocated+1));
		if (!ptr) {
			pthread_mutex_unlock(&mtx);
			return -1;
		}
		memcpy(ptr, job, sizeof(Process_info*)*n_allocated);
		ptr[n_allocated] = NULL;
		n_allocated++;
		free(job);
		job = ptr;
	}
	if (priority == NXT_DONTSORT) {
		job[n_jobs] = new_job;
		n_jobs++;
	} else if (n_jobs > 0) {
		uint32_t pos = 0;
		while (pos < n_jobs && job[pos]->priority >= priority) {
			pos++;
		}
		memmove(&job[pos+1], &job[pos], (n_jobs-pos)*sizeof(Process_info*));
		job[pos] = new_job;
		n_jobs++;
	} else {
		job[0] = new_job;
		n_jobs++;
	}
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	return 0;
}

void Process_handler::exec_callbacks() {
	pthread_mutex_lock(&mtx);
	for (uint32_t x = 0; x < n_jobs; ++x) {
		if (job[x]->callback_ready) {
			if (job[x]->callback) {
				job[x]->callback(job[x]->function_output);
			}
			if (free_input) {
				free(job[x]->function_input);
			}
			free(job[x]->function_output);
			free(job[x]);
			job[x] = NULL;
			n_jobs--;
			memmove(&job[x], &job[x+1], (n_jobs-x)*sizeof(Process_info*));
			x--;
		}
	}
	pthread_mutex_unlock(&mtx);
}

int Process_handler::query_remaining(const uint16_t priority_threshold) {
	uint32_t x = 0, finished = 0;
	pthread_mutex_lock(&mtx);
	while (x < n_jobs && job[x]->priority <= priority_threshold) {
		finished += job[x]->callback_ready;
		x++;
	}
	pthread_mutex_unlock(&mtx);
	return x-finished;
}

extern "C" {
/* C API */
static Process_handler *internal_handler = NULL;

int NXT_init(const uint32_t desired_n_workers, const char input_handled) {
	internal_handler = new Process_handler;
	if (!internal_handler) return -1;
	if (internal_handler->init(desired_n_workers, input_handled)) {
		delete internal_handler;
		internal_handler = NULL;
		return -1;
	}
	return 0;
}

int NXT_add_job(void *(*function)(void *input), void *input, void (*callback)(void *input), const bool sql, const uint16_t priority) {
	return internal_handler->add_job_pri(function, input, callback, sql, priority);
}

int NXT_query_remaining(const uint16_t priority_threshold) {
	return internal_handler->query_remaining(priority_threshold);
}

void NXT_exec_callbacks() {
	internal_handler->exec_callbacks();
}

void NXT_wait_priority(const uint16_t priority) {
	while (internal_handler->query_remaining(priority)) {
		sched_yield();
		continue;
	}
	internal_handler->exec_callbacks();
}

void NXT_exit() {
	if (internal_handler) internal_handler->exit();
}

#ifdef __WIN32
#include <Windows.h>
#elif defined __linux__
#include <sys/sysinfo.h> 
#elif defined __MACOSX__
// do what exactly?
#endif

uint32_t NXT_get_nprocs() {
#ifdef __WIN32
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	uint32_t output;
	output = info.dwNumberOfProcessors;
	if (output > 250) output = 250;
	else if (output == 0) output = 1;
	return output;
#elif defined  __linux__
	uint32_t count = get_nprocs();
	if (count == 0) count = 1;
	else if (count > 250) count = 250;
	return count;
#elif defined __MACOSX__
	uint32_t count;
	size_t size = sizeof(count);
	int mib[] = { CTL_HW, HW_NCPU };
	if (!sysctl(mib, 2, &count, &size, NULL, 0)) {
		if (count > 250) count = 250;
		return count;
	}
	return 1;
#endif
	// default
	return 2;
}

} /* extern "C" */
