#ifndef __MODULES_UTIL_H
#define __MODULES_UTIL_H
#include <nx_include/nx_asset.h>
#include <nx_include/nx_deferred_processing.hpp>

// Starts logging and worker threads.
int mc_util_init(int argc, char **argv);
void mc_util_exit();


void queue_assets_nxt();

// Loads string resource file from @path. Returns 0 on success.
// TODO: migrate this into the asset system and import during critical asset stage.
int mc_load_localization_file(const char *path);

#endif // __MODULES_UTIL_H