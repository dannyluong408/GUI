#ifndef __MODULES_GAME_STATE_H
#define __MODULES_GAME_STATE_H

#include <stdint.h>
#include <signal.h>
#include <pthread.h>
#include <modules/renderer.h>
#include <modules/gameplay.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Game_settings {
	// Video settings
	uint32_t msaa_level;
	double camera_distance, draw_distance;
	double target_framerate;
	double camera_x, camera_y; // Camera rotation angles
	uint8_t render_type; // NO_RENDERER, GL33, GL4*, VK*, etc.
	
	// Performance settings
	// sleep_interval is in microseconds.
	uint32_t n_cores, sleep_interval;
	
	// Network connection
	uint16_t max_ping;
};

class Game_state {
private:
	uint32_t active_state;
	volatile sig_atomic_t should_quit;
	struct renderer_ctx *render_context;
	struct Game_settings settings;
	
	pthread_mutex_t state_mtx;
	pthread_cond_t renderer_cond;
	
	pthread_t renderer_thread, logic_thread;
public:
	Game_state();
	void set_n_cores(const uint32_t n_cores);
	uint32_t get_n_cores() const;
	void set_sleep_int(const uint32_t sleep_interval);
	uint32_t get_sleep_int() const;
	void set_renderer(const uint8_t type);
	int init_window(const uint32_t flags);
	uint8_t quit() const;
	void flag_exit();
	void wait_close();
	int init_threads();
	void set_state(const uint32_t new_state);
	uint32_t get_state() const;
	
	void renderer_block();
	renderer_ctx *get_renderer_context();
};

extern Game_state game_state;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MODULES_GAME_STATE_H