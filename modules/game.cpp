#include "game.h"
#include "user.h"

#include <nx_include/nx_deferred_processing.hpp>
#include <nx_include/nx_error.h>
#include <modules/util.h>

void Game::set_state(const uint8_t new_state) {
    static const char *strings[] = {
		"undefined",
		"initialized_ready",
		"tcp_connected",
		"tcp_authenticated",
		"udp_handshaking",
		"udp_gameplay_active",
		"udp_transition_loading"
	};
	nx_log_msg("game_state: changed from %s to %s.",4,strings[game_state],strings[new_state]);
	game_state = new_state;
}

Game::Game() {
	should_quit = false;
	game_state = state::undefined;
	
	n_entities = 0;
	
    initial_timestamp = nx_get_highres_time_us();
	desired_time = 0;
	server_time = 0;
	desired_step = 5000; // attempt 5ms steps by default.
	active_step = 0;
	
    memset((void*)&current_camera, 0, sizeof(Camera));
}

Game::~Game() {
    for (auto i : users) {
        delete i.second;
	}
}

void Game::step() {
	desired_time += desired_step;
	
	// TODO: remaining game states
	if (game_state == state::udp_gameplay_active) {
		active_step = desired_step;
		if (desired_time - desired_step < nx_get_highres_time_us() - initial_timestamp) {
			// double our step for this frame
			active_step += desired_step;
			desired_time += desired_step;
		}
		// New frame:
		current_frame = new Frame_3D;
		
		
		// do network update here
		// ...
		
		
		// apply our inputs & main player update
		/// ...
		
		// user update
        for (auto u : users) {
            NXT_add_job(update_user, (void*)u.second, NULL, 0, 0);
		}
		
		// generate terrain draw buffer
		// ...
	
		
		// dispatch our draw here
		//NXT_add_job(draw_frame, (void*)current_frame, NULL, 0, 0);
		delete current_frame; // delete it for now.
		
		
		// all finished
		server_time += current_step();
	} else if (game_state == state::undefined) {
		// this first run through allows us to begin our assets asap.
		set_state(state::initialized_ready);
	}
	queue_assets_nxt();
	while (desired_time > nx_get_highres_time_us() - initial_timestamp) {
        nx_usleep(1000);
	}
}

uint32_t Game::current_step() const {
	return active_step;
}

uint64_t Game::now() const {
	return desired_time-active_step;
}

bool Game::quit() const {
	return should_quit;
}

void Game::flag_exit() {
	should_quit = true;
}

#ifndef NDEBUG
void Game::mod_entity_count(const int n) {
	n_entities += n;
}
#endif

void Game::queue_draw(Entity *e) {
	pthread_mutex_lock(&current_frame->mtx);
	current_frame->draw_buffer.push_back(*e);
	pthread_mutex_unlock(&current_frame->mtx);
}

Camera Game::get_camera() const {
	return current_camera;
}
