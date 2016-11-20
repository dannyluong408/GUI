#include <modules/game_state.h>

Game_state::Game_state() {
	memset(this, 0, sizeof(Game_state));
	should_quit = 0;

	
	render_context = new renderer_ctx;
	memset(render_context, 0, sizeof(renderer_ctx));
	
	// settings
	settings.msaa_level = 0;
	settings.camera_distance = 40.0;
	settings.draw_distance = 1000.0;
	settings.target_framerate = 200.0;
	settings.render_type = NX_GL33;
	
	settings.n_cores = 2;
	settings.sleep_interval = 2000;
	
	settings.max_ping = 250;
	
	renderer_cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
	state_mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void Game_state::renderer_block() {
	pthread_mutex_lock(&state_mtx);
	pthread_cond_wait(&renderer_cond, &state_mtx);
}

void Game_state::set_state(const uint32_t new_state) {
	pthread_mutex_lock(&state_mtx);
	active_state = new_state;
	pthread_mutex_unlock(&state_mtx);
}

uint32_t Game_state::get_state() const {
	pthread_mutex_lock(&state_mtx);
	uint32_t ret = active_state;
	pthread_mutex_unlock(&state_mtx);
	return ret;
}

void Game_state::set_n_cores(const uint32_t n_cores) {
	settings.n_cores = n_cores;
}
void Game_state::set_sleep_int(const uint32_t sleep_interval) {
	settings.sleep_interval = sleep_interval;
}
uint8_t Game_state::quit() const {
	return should_quit;
}
uint32_t Game_state::get_n_cores() const {
	return settings.n_cores;
}
void Game_state::set_renderer(const uint8_t type) {
	settings.render_type = type;
}
int Game_state::init_window(const uint32_t flags) {
	if (!init_render_ctx(render_context)) {
		return -1;
	}
	return mylescraft_init_window(&render_context->window, flags, 1024, 768);
}
void Game_state::flag_exit() {
	should_quit = 1;
}

renderer_ctx *Game_state::get_renderer_context() {
	return render_context;
}

uint32_t Game_state::get_sleep_int() const {
	return settings.sleep_interval;
}

int Game_state::init_threads() {
	pthread_attr_t attr;
	if (pthread_attr_init(&attr) || pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)) {
		nx_log_msg("init_threads: pthread attr error",1);
		return -1;
	}
	
	// It's normal-ish for this to fail tbh
	pthread_attr_setstacksize(&attr, 8 * 1024 * 1024);
	
	if (settings.render_type) {
		if (init_window(0)) {
			nx_log_msg("Failed to create window.",1);
			return -1;
		}
		const int ret_r = pthread_create(&renderer_thread, &attr, start_renderer_gl33, (void*)NULL);
		if (ret_r) {
			nx_log_msg("Failed to start renderer thread: %s",1,nx_log_strerror());
			nx_log_strerror_finish();
			return -1;
		}
	}
	const int ret = pthread_create(&logic_thread, &attr, mylescraft_handle_gameplay, (void*)NULL);
	if (ret) {
		nx_log_msg("Failed to start logic thread: %s",1,nx_log_strerror());
		nx_log_strerror_finish();
		return -1;
	}
	return 0;
}

void Game_state::wait_close() {
	should_quit = 1;
	pthread_mutex_lock(&render_context->mtx);
	pthread_cond_signal(&renderer_cond);
	pthread_mutex_unlock(&render_context->mtx);
	pthread_join(renderer_thread, NULL);
	pthread_join(logic_thread, NULL);
}

// Global game state.
Game_state game_state;