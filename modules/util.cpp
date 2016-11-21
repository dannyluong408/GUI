#include <modules/util.h>
#include <nx_include/nx_deferred_processing.hpp>

void queue_assets_nxt() {
	uint32_t count = 0;
	struct nx_asset *pending = get_pending_asset(0);
	while (pending) {
        NXT_add_job(&nx_load_asset, (void*)pending, NULL, 0, 0);
		pending = get_pending_asset(0);
		count++;
	}
	// Don't add low priority assets. They'll just take away disk time.
	// These are critical assets and we have to wait for them all to load.
	if (count) {
		return;
	}
	pending = get_pending_asset(255);
	while (pending) {
        NXT_add_job(&nx_load_asset, (void*)pending, NULL, 0, NXT_DONTSORT);
		pending = get_pending_asset(255);
		count++;
	}
}

int mc_util_init(int argc, char **argv) {
	assert(argc && argv && argv[0]);
	const int ret = nx_init_asset_handler(argv[0]);
	if (ret) {
		printf("nx_init_asset_handler() returned %i\n",ret);
		return -1;
	}
	char *error_path = nx_asset_translate_path("error.log");
	if (!error_path) {
		printf("nx_asset_translate_path error.\n");
		return -2;
	}
	if (nx_log_init(error_path)) {
		printf("Error setting up error log. Logging isn't available.\n");
	}
	free(error_path);
	const uint32_t nprocs = NXT_get_nprocs();
	if (NXT_init(nprocs, 1)) {
        nx_log_msg("Failed to start worker pool with %lu threads.",1,nprocs);
		return -3;
	} else {
        nx_log_msg("Started worker pool with %lu threads.",3,nprocs);
	}
	
	return 0;
}

void mc_util_exit() {
	NXT_exit();
	nx_log_exit();
}
