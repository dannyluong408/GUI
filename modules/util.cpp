#include <modules/util.h>

void queue_assets_nxt() {
	uint32_t count = 0;
	struct nx_asset *pending = get_pending_asset(0);
	while (pending) {
		NXT_add_job(nx_load_asset, (void*)pending, NULL, 0, 0);
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
		NXT_add_job(nx_load_asset, (void*)pending, NULL, 0, NXT_DONTSORT);
		pending = get_pending_asset(255);
		count++;
	}
}