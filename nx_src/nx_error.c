#include <nx_error.h>

#define NX_DEFAULT_OUTPUT stdout

#ifdef __cplusplus
extern "C" {
#endif

static int setup = 0;
char *invalid_msg = "Unknown error (message failed to save)";

struct NX_LOG_INTERNAL {
	FILE *log_file;
	char *filename;
	char *crit_error;
	uint8_t suppress_level;
	uint8_t quit;
	pthread_mutex_t mtx;
	
	pthread_mutex_t strerror_mtx;
};
static struct NX_LOG_INTERNAL internal;

int nx_log_init(const char *log_path) {
	if (!setup) {
		internal.suppress_level = 4;
		internal.quit = 0;
		internal.filename = NULL;
		internal.crit_error = NULL;
		internal.log_file = NULL;
		internal.mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		internal.strerror_mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		if (log_path) {
			open_file:
			internal.log_file = fopen(log_path, "a");
			if (!internal.log_file) {
				nx_log_msg("Failed to open file '%s' for writing: %s.",2,log_path,nx_log_strerror());
				nx_log_strerror_finish();
			} else {
				const uint32_t len = strlen(log_path) + 1;
				internal.filename = malloc(len);
				if (internal.filename) {
					memcpy(internal.filename, log_path, len);
				} // otherwise ignore
			}
		}
		fprintf(NX_DEFAULT_OUTPUT,"Output log set to %s. Warn level is <%u.\n",log_path,internal.suppress_level);
		setup = 1;
	} else {
		if (internal.log_file) {
			nx_log_msg("Log file '%s' already opened. Ignoring nx_log_init(%s).",2,internal.filename,log_path);
		} else if (log_path) {
			goto open_file;
		}
	}
	return 0;
}

void nx_log_msg(const char *msg, const uint8_t level, ...) {
	if (level > internal.suppress_level) {
		return;
	}
	char buffer[4000];
	va_list args;
	va_start(args, level);
	vsnprintf(buffer, sizeof(buffer)-2, msg, args);
	va_end(args);
	const int len = strlen(buffer);
	// Append a newline 
	buffer[len] = '\n';
	buffer[len+1] = 0;
	pthread_mutex_lock(&internal.mtx);
	fputs(buffer, NX_DEFAULT_OUTPUT);
	#ifdef DEBUG
	// want to flush this for crash logs
	fflush(NX_DEFAULT_OUTPUT);
	#endif
	if (internal.log_file) {
		fputs(buffer, internal.log_file);
	}
	if (level == NX_EXIT) {
		internal.quit = 1;
		internal.crit_error = malloc(len+2);
		if (internal.crit_error) {
			memcpy(internal.crit_error, buffer, len+2);
		} else {
			internal.crit_error = invalid_msg;
		}
		fflush(NX_DEFAULT_OUTPUT);
		fflush(internal.log_file);
	}
	pthread_mutex_unlock(&internal.mtx);
}

int nx_check_error() {
	return internal.quit;
}

char *nx_get_errmsg() {
	return internal.crit_error;
}

char *nx_log_strerror() {
	const int err = errno;
	pthread_mutex_lock(&internal.strerror_mtx);
	return strerror(err);
}

void nx_log_strerror_finish() {
	pthread_mutex_unlock(&internal.strerror_mtx);
}

void nx_log_suppress(const uint8_t level) {
	if (!level) internal.suppress_level = 255;
	else internal.suppress_level = level;
}

void nx_log_exit() {
	fflush(NX_DEFAULT_OUTPUT);
	fflush(internal.log_file);
#ifdef __WIN32
	// Winpthread specifically states that you "may" have to do this. It seems to work.
	pthread_mutex_destroy(&internal.mtx);
	pthread_mutex_destroy(&internal.strerror_mtx);
#endif
	if (internal.log_file) fclose(internal.log_file);
	internal.log_file = NULL;
	free(internal.filename);
	internal.filename = NULL;
}

void nx_display_popup_msg(const char *title, const char *errmsg, ...) {
	char buffer[5000];
	va_list args;
	va_start(args, errmsg);
	vsnprintf(buffer, sizeof(buffer)-1, errmsg, args);
	va_end(args);
	#ifdef __WIN32
	MessageBox(NULL, buffer, title, MB_OK | MB_TASKMODAL);
	#else
		#ifndef NX_ERROR_USING_CLI
			#warning "no supported message dialog, using default output stream"
		#endif
	fputs(buffer, NX_DEFAULT_OUTPUT);
	#endif
}

#ifdef __cplusplus
}
#endif