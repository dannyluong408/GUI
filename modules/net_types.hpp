#pragma once
#include <stdint.h>

#include "gc_protocol.hpp"

#define GAME_VERSION 320

#define NETWORK_PING_TIMEOUT 10000 // milliseconds
#define NETWORK_PING_VARIANCE 50


//#define USE_SMALL_IDS

// Primitives

#define WORLD_USER 0
#ifdef USE_SMALL_IDS
#define NULL_PLAYER_ID 0xffff
typedef uint16_t PLAYER_ID;
#else
#define NULL_PLAYER_ID 0xffffffff
typedef uint32_t PLAYER_ID;
#endif

typedef uint32_t WORLD_ID;
#define NULL_WORLD_ID 0xffffffff

typedef uint16_t SPELL_ID;
typedef uint16_t BUFF_ID;
typedef uint8_t SERVER_MESSAGE;

// Network packet sub-header. First bytes of any encrypted packet from the client.
struct __attribute__ ((__packed__)) network_packet_header {
	PLAYER_ID player_id;
};

// Encryption initialization vector & packet ID
union IV {
	unsigned char b[4];
	uint32_t i;
};

struct __attribute__ ((__packed__)) vec3f {
	float x,y,z;
};

struct __attribute__ ((__packed__)) keybind_key {
	uint8_t key, mod;
};

struct __attribute__ ((__packed__)) target_entity {
	PLAYER_ID id;
	// Targeting pets and child entities.
	uint16_t sub_id;
};

// Spell target identifier. 
union __attribute__ ((__packed__)) target_t {
	target_entity t;
	vec3f position;
};
// Precise time identifier, to be compared with other precise_time_t instances.
struct __attribute__ ((__packed__)) precise_time_t {
	uint64_t game_time;
	uint32_t order;
};

// CP_UPDATE_MOVESTATE
struct __attribute__ ((__packed__)) movement_state {
	vec3f position;
	float facing_angle;
	// move_state = 0xff is undefined state. do not draw. do not update.
	uint8_t move_state;
};
// End of primitive types


// SP_REMOVE_PLAYER 
struct __attribute__ ((__packed__)) remove_player_event {
	PLAYER_ID player;
	//uint8_t options; // what for?
};

// SP_CHANGE_TARGET
struct __attribute__ ((__packed__)) change_target_event {
	target_entity entity, target;
};

// SP_RESET_COOLDOWNS
struct __attribute__ ((__packed__)) cd_reset_event {
	PLAYER_ID player;
};

// SP_UPDATE_MOVESTATE
struct __attribute__ ((__packed__)) server_move_event {
	movement_state ms;
	target_entity entity;
};

// SP_UPDATE_MOVESTATE_EXT, CP_UPDATE_MOVESTATE_EXT - both unused
/* Extended movement state which records player perspective.
 * This may be used by default in the future. 
 * Worlds flagged as WORLD_TOURNAMENT_GAME will require this for replays. 
 * Server component unlikely to be used. */
struct __attribute__ ((__packed__)) movement_state_ext {
	movement_state ms;
	// As percentages 0-100 of screen height and width.
	uint8_t cursor_x, cursor_y;
	float camera_x, camera_y;
	uint8_t mouse_visible;
};

// SP_FORCE_MOVEMENT
// Forces a movement state overwrite.
struct __attribute__ ((__packed__)) movement_state_forced {
	vec3f position;
	float facing_angle;
	//uint16_t animation; 
};

// SP_JUMP_EVENT, CP_JUMP_EVENT
struct __attribute__ ((__packed__)) jump_event {
	vec3f origin;
	float movement_angle;
	uint8_t move_state;
	PLAYER_ID id;
};

// SP_NUDGE_EVENT, CP_NUDGE_EVENT
struct __attribute__ ((__packed__)) nudge_event {
	float facing_angle;
	uint8_t move_state;
	PLAYER_ID id;
};

// CP_UPDATE_SETTINGS
// Client reported settings.
struct __attribute__ ((__packed__)) client_settings_t {
	/* Enable VOIP transmit/receive */
	uint8_t enable_voice;
	/* Flag for low bandwdith, trading off some real-time updates for less network overhead. 
	 * Depending on combat situations, this can reduce bandwidth by 20-50%. */
	uint8_t low_network_settings;
	uint16_t max_ping; // Max acceptable mm ping. Minimum 100.
	uint16_t ability_queue_threshold;
};

// REMOVED
// This packet has no identifier. It is the only packet sent by the client without encryption.
// Client connect packet. Public key should be known on the client.
struct __attribute__ ((__packed__)) network_connect_REMOVED {
	uint16_t client_version;
	unsigned char public_key_hash[16];
	unsigned char public_key[256];
};

// SP_CONFIRM_CONNECT
struct __attribute__ ((__packed__)) network_confirm_connect {
	PLAYER_ID client_id;
	uint64_t server_time;
	uint8_t content_encryption_key[16];
};

// CP_AUTHME - REMOVED
struct __attribute__ ((__packed__)) network_login_REMOVED {
	/* @pw is a SHA256 hash of the user's input password.
	* If @is_token is nonzero, the password field is used for a session token. */
	char name[NAME_MAXLEN];
	uint8_t pw[32];
	uint8_t is_token;
};

// CP_CONNECT 
struct __attribute__ ((__packed__)) network_connect {
	uint16_t client_version;
	uint32_t account_id;
	uint8_t identifier[32]; // hash of encryption key
};

// SP_PLAYER_INFO
// Also used for changing classes. If old class != 0, an animation should be played.
struct __attribute__ ((__packed__)) network_player_data {
	target_entity player;
	uint16_t class_id, health, health_max, resource, resource_max;
	uint8_t move_speed, magic_armor, physical_armor, slow_suppression, combat_state;
	uint8_t relationship;
	target_entity target;
	char name[NAME_MAXLEN];
};

// SP_CONFIRM_LOGIN
struct __attribute__ ((__packed__)) network_confirm_login {
	// Update use id to this new player_data.player_id.
	network_player_data player_data;
	uint64_t current_server_time;
	uint8_t server_region;
	uint16_t server_id;
	uint16_t version_high, version_low, tickrate;
};


// SP_UPDATE_HEALTH_RESOURCE_STATE
struct __attribute__ ((__packed__)) network_health_resource_state {
	uint16_t health, health_max, resource, resource_max;
	precise_time_t time;
	target_entity target;
};

// SP_UPDATE_BUFF
struct __attribute__ ((__packed__)) network_buff {
	target_entity target;		// entity id of the target
	PLAYER_ID caster_id;	// player id of the caster
	uint64_t expire_time;	// expire time (on server)
	BUFF_ID buff_id;		// see spells.h
	int32_t value;
	uint16_t instance;		// this serves as the unique position of the buff
	precise_time_t origin_time;
};

// CP_CANCEL_BUFF
struct __attribute__ ((__packed__)) cancel_buff {
	uint16_t instance;
};

// SP_DAMAGE_INSTANCE
struct __attribute__ ((__packed__)) network_damage {
	target_entity target, damager;
	precise_time_t time;
	uint16_t damage, absorb;
	SPELL_ID spell_id;
};

// SP_SPELL_QUEUED
struct __attribute__ ((__packed__)) spell_queue_event {
	uint16_t spell_id;
	// Amount of time from current server time.
	uint32_t when;
	uint64_t current_server_time;
};

// SP_SPELL_USED, SP_START_CAST
struct __attribute__ ((__packed__)) spell_cast_event {
	uint16_t spell_id;
	// Necessary?
	//int32_t value;
	target_t target;
	target_entity caster;
};

// SP_UPDATE_COMBAT_STATE
struct __attribute__ ((__packed__)) combat_state_event {
	uint8_t in_combat;
	PLAYER_ID player;
	precise_time_t time;
};

// SP_INTERRUPT_EVENT
struct __attribute__ ((__packed__)) interrupt_t {
	target_entity interrupted, interrupter;
	SPELL_ID spell_id;
	// In milliseconds
	uint16_t lockout_time;
};

// SP_PLAYER_DISCONNECT
// Flag this player as disconnected (not logged out).
// In the future this should allow teammates to control disconnected players.
struct __attribute__ ((__packed__)) disconnect_event {
	PLAYER_ID player;
};

// SP_PLAYER_RECONNECT
struct __attribute__ ((__packed__)) reconnect_event {
	PLAYER_ID player;
};

// SP_TIME_UPDATE
struct __attribute__ ((__packed__)) time_reply_t {
	uint64_t time;
	uint32_t token;
};

// SP_ACK, CP_ACK
struct __attribute__ ((__packed__)) acknowledge_t {
	IV iv;
};

// CP_CAST_SPELL
struct __attribute__ ((__packed__)) request_cast_spell {
	SPELL_ID spell_id;
	target_t target;
};

// CP_REQUEST_COMBAT_STATE, CP_REQUEST_USER_INFO, CP_REQUEST_BUFF_DUMP
struct __attribute__ ((__packed__)) target_state_request {
	target_entity target;
};

// CP_CHANGE_TARGET
struct __attribute__ ((__packed__)) client_target {
	target_entity new_target;
};

// CP_REQUEST_BUFF_INFO
struct __attribute__ ((__packed__)) buff_instance_request {
	target_entity target;
	uint16_t instance;
};

// CP_REQUEST_TIME
struct __attribute__ ((__packed__)) time_token {
	// To be returned in time_reply_t
	uint32_t token;
};

// CP_REPORT_LATENCY
struct __attribute__ ((__packed__)) latency_report {
	// All times in microseconds.
	uint32_t recent;
	float avg;
};


// length bytes after the end of chat_packet will be used for the message.
struct __attribute__ ((__packed__)) whisper_packet {
	PLAYER_ID sender;
	uint16_t length;	// length of bytes to read beyond this packet
};

struct __attribute__ ((__packed__)) chat_msg_packet {
	PLAYER_ID sender;
	uint32_t channel, channel_ext;
	uint16_t length; // number of bytes to read beyond this struct.
};

// SP_SWITCH_WORLD
struct __attribute__ ((__packed__)) world_settings_t {
	// Map ID corresponding to map file.
	uint8_t map_id;
	// Max updaterate and min updaterate (for net_quality=low). Client is free to use anything between the two.
	uint8_t max_updaterate, min_updaterate;	
	// Region ID corresponding to host location (US east, EU west, etc).
	uint8_t server_region;
	
	// Max distance in which players will receive updates from other players. 
	// This may be reduced with net_quality = low as well as adjusted due to overpopulation.
	uint16_t update_range; 
	
	// Bit-flags for world settings.
	uint8_t settings;
	// World ID for use in switching.
	uint32_t world_id;
	// Keepalive time in milliseconds.
	uint32_t keepalive_time;
	
	movement_state new_state;
};

enum {
	COOLDOWN_UPDATE_MODE_MOD = 1,	// add to the current cooldown state
	COOLDOWN_UPDATE_MODE_SET = 2,	// set cooldown time
	COOLDOWN_UPDATE_MODE_ZERO = 3,	// zero the cooldown
	
	// Used when updating a controlled target's cooldowns.
	COOLDOWN_CONTROLLER_CONTEXT_BIT = 128
};

// SP_SPELL_NOT_READY, SP_COOLDOWN_STATE
struct __attribute__ ((__packed__)) cooldown_state_t {
	uint8_t mode;
	SPELL_ID spell_id;
	uint64_t data;	// amount to modify by
};

// SP_COOLDOWN_STATE_EXT
// Update teammate cooldowns for team cd tracking.
// May also be used for spectator interface.
// Currently unused.
struct __attribute__ ((__packed__)) cooldown_state_ext {
	PLAYER_ID player;
	cooldown_state_t cd_state;
};

// SP_SPELL_ERROR
struct __attribute__ ((__packed__)) spell_error_t {
	uint8_t errmsg;
	SPELL_ID spell;
	target_t target;
};

// SP_DUMP_KEYINFO, CP_UPDATE_KEYINFO
struct __attribute__ ((__packed__)) keybind_set_t {
	// secondary_spells used in stealth or w/e.
	SPELL_ID action_spells[5][10], secondary_spells[10];
	keybind_key action_bar[5][10],
		// Movement
		move_left, move_right, move_forward, move_back, move_jump,
		turn_right,	turn_left,
		// Target
		target[5], target_enemy[5], target_nearest_enemy, target_nearest_friendly,
		// Social
		whisper, re_whisper, open_chat,
		// Misc
		toggle_spellbook, camera_in, camera_out,
		screenshot, toggle_menu, queue_menu, customization_menu,
		control_disconnected_player;
	uint8_t activate_on_key_up;
	/* Info that isn't stored in the sql db must be stored at the end of the struct. */
	uint16_t class_id;
};

enum {
	REGION_UNKNOWN = 0,	// AKA "dontcare" region in some cases
	
	REGION_US_WEST = 1,
	REGION_US_EAST = 2
	
	//REGION_EU_WEST = 21
};

enum {
	MOVEMENT_FORWARD = 1,
	MOVEMENT_BACKWARD = 2,
	MOVEMENT_LEFT = 4,
	MOVEMENT_RIGHT = 8,
	// Slow walk mode.
	MOVEMENT_WALKING = 16,
	
	MOVEMENT_JUMPING = 128
};

// Player relationships
enum {
	RELATIONSHIP_SELF = 0,
	RELATIONSHIP_FRIENDLY = 1,
	RELATIONSHIP_ENEMY = 2,
	RELATIONSHIP_NEUTRAL = 3,
	// relationship hasn't changed, but everything else has.
	RELATIONSHIP_UNKNOWN_DONTCHANGE = 4,
	
	RELATIONSHIP_PARTY_FLAG = 64,
	RELATIONSHIP_CANT_HELP_FLAG = 128
};

// attack types - superior versions use different rules (no miss, etc)
enum {
	SPELL_RANGE,
	SPELL_MAGIC,
	SPELL_MELEE,
	
	SPELL_RANGE_SUPERIOR,
	SPELL_MAGIC_SUPERIOR,
	SPELL_MELEE_SUPERIOR
};

// Spell error types 
enum {
	SPELL_ERROR_SUCCESS = 0,
	/* Used internally by vanish projectile & short immunity. */
	SPELL_ERROR_TARGET_VANISH = 1,
	SPELL_ERROR_TARGET_IMMUNE = 2,
	SPELL_ERROR_TARGET_DODGED = 3,
	SPELL_ERROR_ATTACK_MITIGATED = 4,
	SPELL_ERROR_ATTACK_FULLY_ABSORBED = 5,
	
	SPELL_ERROR_REQUIRES_OUT_OF_COMBAT = 6,
	SPELL_ERROR_NOT_ENOUGH_RESOURCE = 7
};


// not used yet
enum {
	DUEL_CANCEL = 2,
	DUEL_ACCEPT = 3,
	DUEL_COMPLETED = 4,
	DUEL_CANCELED = 5,
	DUEL_STARTING = 6
};
// Disconnect messages
enum {
	DISCONNECT_SESSION_EXPIRED = 1,
	DISCONNECT_USER_LOGGED_IN_ELSEWHERE = 2,
	DISCONNECT_USER_REQUESTED = 3,
	DISCONNECT_SERVER_SHUTTING_DOWN = 4,
	DISCONNECT_CONNECT_THROTTLED = 5
};

// Network message error codes
enum {
	MSG_SUCCESS = 0,
	MSG_FAILED_USER_BLOCKED = 1,
	MSG_FAILED_USER_NOT_FOUND = 2,
	MSG_FAILED_NOT_IN_CHAT = 3,
};

enum {
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
};

// Server error codes.
enum {
	CLIENT_OUT_OF_DATE = 1,
	CLIENT_SERVER_VERSION_MISMATCH = 2, // only to be used if client_version > server_version
	INVALID_LOGIN = 3,
	INVALID_COMMAND = 4,
	//KEY_EXCHANGE_ERROR = 5,
	UNSPECIFIED_ERROR_PLEASE_RETRY = 6,
	SERVER_FULL = 7, // need to implement a queue possibly.
	SESSION_EXPIRED = 8,
	INVALID_CONNECTION_WRONG_KEY = 9,
	GC_OFFLINE = 10
};

// Server state messages.
enum {
	// Force pause. A SP_FORCE_MOVEMENT should follow.
	SM_PAUSE_GAMEPLAY = 0,
	// Allow movement and spellcasting again.
	SM_UNPAUSE_GAMEPLAY = 1,
	SM_INVALID_COMMAND = 2,
	SM_INVALID_TARGET = 3,
	SM_GCD_ERROR = 4,
};

enum world_settings_flags {
	WORLD_SPECTATORS_ENABLED = 1,
	WORLD_REPLAY_ENABLED = 2,
	WORLD_ALLOW_DUELS = 4,
	WORLD_TOURNAMENT_GAME = 8 // implies faster update rates among other things
};

enum {
	NEGOTIATION_PACKET = 0,
	ENCRYPTED_PACKET = 1,
	ENCRYPTED_PACKET_PLEASE_ACKNOWLEDGE = 2,
	AUXILLARY_PROTOCOL_PACKET = 3,
};

/* Server packet types. Format comments include the 1 byte type identifier. */
enum {
	// Non-critical server message. Length of SERVER_MESSAGE.
	SP_MESSAGE = 0, 
	// Critical server messages. Length of SERVER_MESSAGE.
	// SP_ERROR apparently taken by winapi thanks dude
	SP_ERRMSG = 1,
	// Disconnect messages. Length of SERVER_MESSAGE.
	SP_DISCONNECT = 2,
	// See: spell_error_t
	SP_SPELL_ERROR = 3,
	
	// See: network_confirm_connect
	SP_CONFIRM_CONNECT = 4,
	// See: network_confirm_login
	SP_CONFIRM_LOGIN = 5,
	// See: remove_player_event
	SP_REMOVE_PLAYER = 6,	// tell clients to remove the player
	// See: network_player_data
	SP_PLAYER_INFO = 7,
	// See: network_buff
	SP_UPDATE_BUFF = 8,

	// See: server_move_event
	SP_UPDATE_MOVESTATE = 10,
	SP_UPDATE_MOVESTATE_EXT = 11,
	// See: network_damage
	SP_DAMAGE_INSTANCE = 12,
	// See: spell_queue_event
	SP_SPELL_QUEUED = 13,
	// See: cooldown_state_t
	SP_SPELL_NOT_READY = 14,

	// See: spell_cast_event. SP_SPELL_USED is sent on completion, SP_START_CAST sent on beginning.
	SP_SPELL_USED = 16,
	SP_START_CAST = 17,
	
	// See: combat_state_event
	SP_UPDATE_COMBAT_STATE = 20,

	// See: health_resource_state
	SP_UPDATE_HEALTH_RESOURCE_STATE = 21,
	// See: world_settings_t
	SP_SWITCH_WORLD = 23,
	
	// UNKNOWN - probably damage codes
	//SP_SPELL_ERROR = 24,
	
	// See: change_target_event
	SP_CHANGE_TARGET = 26,
	
	// See: reset_cooldowns
	SP_RESET_COOLDOWNS = 27,
	// See: interrupt_t
	SP_INTERRUPT_EVENT = 28,
	// See: movement_state_forced
	SP_FORCE_MOVEMENT = 29,
	// See: disconnect_event
	SP_PLAYER_DISCONNECTED = 30,
	// See: reconnect_event
	SP_PLAYER_RECONNECTED = 31, // when the player reconnects (to remove dc indicator)
	// See: cooldown_state_t
	SP_COOLDOWN_STATE = 32, // modified 
	// See: cooldown_state_ext
	SP_COOLDOWN_STATE_EXT = 33,
	// See: time_reply_t
	SP_TIME_UPDATE = 34,

	// TEMPORARILY DISABLED
	//SP_DUEL = 36,
	
	// See: keybind_set_t
	SP_DUMP_KEYINFO = 37,

	// See: cd_reset_event
	SP_RESET_BUFFS = 40,
	
	
	// See: jump_event
	SP_JUMP_EVENT = 100,
	// See: nudge_event
	SP_NUDGE_EVENT = 101,
	
	// See: server_ack_t 
	SP_ACK = 255
};

// client specific packet types
enum {
	CP_ANNOUNCE = 0, // unused
	// See: network_login REMOVED
	// CP_AUTHME = 1,
	// See: movement_state
	CP_UPDATE_MOVESTATE = 2,
	// See: movement_state_ext
	CP_UPDATE_MOVESTATE_EXT = 3, 
	
	// Temporarily disabled
	//CP_USING_CONTEXT = 4,	// Packet header for setting packet command for a different target.
	//CP_REQUEST_CONTROL = 5,
	
	
	CP_DISCONNECT_ME = 6,
	// See: cancel_buff
	CP_CANCEL_BUFF = 7,
	
	// See: acknowledge_t
	CP_ACK = 8,
	// See: request_cast_spell
	CP_CAST_SPELL = 9,
	
	// See: target_state_request 
	// removed probably
	//CP_REQUEST_COMBAT_STATE = 10,
	
	// See: client_target
	CP_CHANGE_TARGET = 11,
	
	//CP_CONFIRM_WORLD_CHANGE = 12, // implemented but not used
	// See: target_state_request 
	CP_REQUEST_USER_INFO = 13,
	// See: buff_instance_request
	CP_REQUEST_BUFF_INFO = 14,
	// See: target_state_request
	CP_REQUEST_BUFF_DUMP = 15,
	// See: client_settings_t
	CP_UPDATE_SETTINGS = 16,
	// See: time_token
	CP_REQUEST_TIME = 17,
	// See: latency_report
	CP_REPORT_LATENCY = 18,
	
	
	// See: keybind_set_t
	CP_UPDATE_KEYINFO = 19,
	
	// See: jump_event
	CP_JUMP_EVENT = 20,
	// See: nudge_event
	CP_NUDGE_EVENT = 21,
	
	CP_RESERVED = 255
};
