#ifndef __NX_ERROR_H
#define __NX_ERROR_H

#ifdef __WIN32
#include "Windows.h"
#endif

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define NX_EXIT 1

#ifdef __cplusplus
extern "C" {
#endif

int nx_log_init(const char *log_path);
void nx_log_exit();
// Set log suppress level. All messages above @level are ignored.
void nx_log_suppress(const uint8_t level);
void nx_log_msg(const char *msg, const uint8_t level, ...);
// Check if NX_EXIT level or below errors have been logged. The error string can be read with nx_get_errmsg().
int nx_check_error();
char *nx_get_errmsg() __attribute__ ((__cold__));
void nx_display_popup_msg(const char *title, const char *errmsg, ...) __attribute__ ((__cold__));
// strerror wrapper functions. nx_log_strerror_finish() must be called after each nx_log_strerror().
char *nx_log_strerror();
void nx_log_strerror_finish();

#ifdef __cplusplus
}
#endif

#endif // __NX_ERROR_H