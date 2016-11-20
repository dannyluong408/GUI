#ifndef __MODULES_UTIL_H
#define __MODULES_UTIL_H
#include <nx_include/nx_asset.h>
#include <nx_include/nx_deferred_processing.hpp>

struct map {
	nx_asset *data;
	char hash[32];
};

void queue_assets();
void build_maps();

#endif // __MODULES_UTIL_H