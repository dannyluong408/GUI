#ifndef __MODULES_INIT_H
#define __MODULES_INIT_H

#include <pthread.h>
#include <nx_include/nx_error.h>
#include <nx_include/nx_asset.h>
#include <nx_include/nx_deferred_processing.hpp>
#include <modules/game_state.h>
#include <modules/renderer.h>

int mc_init(const int argc, char **argv);
void mc_close();

#endif // __MODULES_INIT_H