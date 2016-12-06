#pragma once
#include <stdint.h>

#define COORDINATOR_PROTOCOL 1
#define COORDINATOR_PORT 3221

#define NAME_MAXLEN 33

enum {
	REGION_USE = 0,
	// Beauharnois QC, CA
	REGION_USE_BHS = 1,
	REGION_USC = 20,
	REGION_CJK = 30,
	REGION_EUC = 40,
	// Falkenstein, DE
	REGION_EUC_FKS = 41,
};

struct __attribute__ ((__packed__)) GC_frame {
	uint64_t id;
	uint32_t len;
};

struct __attribute__ ((__packed__)) GS_name {
	char name[65];
};

struct __attribute__ ((__packed__)) GC_key {
	uint8_t byte[129];
};


struct __attribute__ ((__packed__)) GA_GS_list_header {
	uint32_t version_gc;
	uint32_t n_nodes;
};

// All IPs and ports are stored in network byte order
struct __attribute__ ((__packed__)) GS_list_entry {
	uint8_t ip4[4];
	uint8_t ip6[16];
	uint16_t p4, p6;
	uint16_t region;
	uint32_t n_players;
};

// GS_AUTHME
struct __attribute__ ((__packed__)) GS_auth_server {
	uint64_t header; // must be UINT64_MAX
	GC_key key;
	uint32_t version_gc;
	uint32_t version_gs;
	// network-endian IPs and ports reported by earlier response.
	// we don't have a good way to confirm these, so they're more or less trusted with the private key.
	// do not convert from network-endian
	uint8_t ip4[4];
	uint8_t ip6[16];
	// these can technically be different. the gs currently makes no distinction though.
	uint16_t p4, p6;
	uint8_t rc; // 0 for cold start, 1 for reconnect
};

// GS_AUTH_USER
struct __attribute__ ((__packed__)) GS_auth_user {
	char name[NAME_MAXLEN];
	uint8_t pw[32];
	// is_token == 0 means traditional password-based auth
	uint8_t is_token;
};

struct __attribute__ ((__packed__)) GC_return_ip {
	uint8_t af;
	uint8_t addr[16];
	uint16_t port;
};

// GA_AUTHME
struct __attribute__ ((__packed__)) GA_auth_server {
	uint64_t header;
	GC_key key;
	uint32_t version_ga;
};

// GC_AUTH_RESPONSE
struct __attribute__ ((__packed__)) GC_auth_response {
	GS_name name;
	uint32_t server_id;
	uint16_t region;
	uint32_t performance;
	
	uint8_t req_resync;
	uint8_t configure_as_proxy;
};

// GS -> GC packets
enum {
	GS_HEARTBEAT = 0,
	GS_AUTHME = 1,
	GS_AUTH_USER = 2,
	GS_REQUESTING_IP = 3,
	GS_REQUESTING_GS_LIST = 4,
};

enum {
	GA_HEARTBEAT = 0,
	GA_AUTH = 1,
};

// GC -> GS packets
enum {
	GC_HEARTBEAT = 0,
	//GC_AUTH_SERVER = 1,
	//GC_SET_SERVER_SETTINGS = 2,
	GC_REMOVE_USER = 3,
	GC_RETURN_IP = 4,
	GC_RETURN_LIST = 5,
	
	GC_AUTH_USER = 100,
	
	GC_SERVER_AUTH_ERROR = 200,
	GC_SERVER_SHUTTING_DOWN = 201,
};
