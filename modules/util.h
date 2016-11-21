#ifndef __MODULES_UTIL_H
#define __MODULES_UTIL_H
#include <nx_include/nx_asset.h>
#include <nx_include/nx_deferred_processing.hpp>

int mc_util_init(int argc, char **argv);
void mc_util_exit();
void queue_assets_nxt();

#endif // __MODULES_UTIL_H