#include <stdint.h>
#include <stdlib.h>

#ifdef __WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#define NX_UDP 1
#define NX_TCP 2

struct nx_net_addr {
	#ifdef __WIN32
	SOCKADDR_IN6 addr;
	#else
	struct sockaddr_in6 addr;
	#endif
};

struct nx_net_socket {
	uint8_t sock_type;
	#ifdef __WIN32
	SOCKET socket;
	#else
	int socket;
	#endif
};


int nx_net_init(const uint8_t mode, const uint16_t port, struct nx_net_socket *use_socket);

// Returns number of bytes stored in output on success or negative on failure.
int nx_net_read(struct nx_net_socket *sock, unsigned char *output, const uint32_t maxlen, struct sockaddr_in6 *addr_out);
// returns negative on failure
int nx_net_write(struct nx_net_socket *sock, const unsigned char *msg, const uint16_t len, const struct sockaddr_in6 *target);

void nx_net_close(struct nx_net_socket *use_socket);
void nx_net_cleanup();