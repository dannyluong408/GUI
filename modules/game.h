#pragma once
#include <stdint.h>
#include <signal.h>
#include <pthread.h>
#include <unordered_map>
#include <vector>
#include <nx_include/nx_timing.h>
#include <modules/net_types.hpp>
#include <modules/user.h>

#include "camera.h"

namespace state {
	enum : uint8_t {
		undefined,
		initialized_ready,
		tcp_connected,
		tcp_authenticated,
		udp_handshaking,
		udp_gameplay_active,
		udp_transition_loading
	};
};

struct Frame_3D {
	std::vector<Entity> draw_buffer;
	pthread_mutex_t mtx = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
};


class Game {
private:
	sig_atomic_t should_quit, game_state;
	std::unordered_map<PLAYER_ID, User*> users;
	
	Frame_3D *current_frame;
	
	uint64_t n_entities;
	
	// All time instances are in microseconds
	uint64_t initial_timestamp, desired_time, server_time, desired_step;
	uint32_t active_step;
	
	Camera current_camera;
	
	void set_state(const uint8_t new_state);
public:
	Game();
	~Game();
	
	void step();
	uint32_t current_step() const;
	uint64_t now() const;
	WORLD_ID current_world() const;
	
	
	bool quit() const;
	void flag_exit();
	#ifndef NDEBUG
	void mod_entity_count(const int n);
	#endif
	void queue_draw(Entity *e);
	Camera get_camera() const;
};

extern Game game;
