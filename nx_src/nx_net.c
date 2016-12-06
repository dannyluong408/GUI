#include <nx_net.h>

#ifdef __WIN32
int status = 0;
#endif

int nx_net_init(const uint8_t mode, const uint16_t port, struct nx_net_socket *use_socket) {
	if (!use_socket) return -1;
	if (mode != NX_UDP && mode != NX_TCP) return -1;
	use_socket->sock_type = mode;
	sockaddr_in6 listening_addr;
	memset(&listening_addr, 0, sizeof(sockaddr_in6));
	listening_addr.sin6_family = AF_INET6;
	listening_addr.sin6_port = htons(port);
	#ifdef __WIN32
	listening_addr.sin6_addr = IN6ADDR_ANY;
	#else
	listening_addr.sin6_addr = in6addr_any;
	#endif
	if (mode == NX_UDP) {
		#ifdef __WIN32
		// don't WSAStartup multiple times
		if (!status) {
			WSADATA WsaData;
			if (WSAStartup(MAKEWORD(2,2), &WsaData)) {
				WSACleanup();
				return -1;
			}
		}
		use_socket->socket = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
		if (use_socket->socket == SOCKET_ERROR) {
			return -2;
		}
		u_long mode = 1;
		if (ioctlsocket(UDPsock, FIONBIO, &mode)) {
			return -3;
		}
		if (bind(use_socket->socket, (struct sockaddr*)&listening_addr, sizeof(listening_addr)) == SOCKET_ERROR){ 
			return -4;
		}
		#else
		use_socket->socket = socket(AF_INET6, SOCK_DGRAM, 0);
		if (use_socket->socket == -1) {
			return -1;
		}
		if (bind(use_socket->socket, (struct sockaddr*)&listening_addr, sizeof(listening_addr)) == -1) {
			return -2;
		}
		#endif
		use_socket->udp_internal = malloc(sizeof(struct nx_udp_history));
		if (!use_socket->udp_internal) {
			return -5;
		}
	} else {
		return -1; // no tcp for now
	}
	return 0;
}

void nx_net_close(struct nx_net_socket *use_socket) {
	#ifdef __WIN32
	closesocket(use_socket->socket);
	#else
	close(use_socket->socket);
	#endif
}

int nx_net_read(struct nx_net_socket *sock, unsigned char *output, const uint32_t maxlen, struct sockaddr_in6 *addr_out) {
	socklen_t socket_len = sizeof(struct sockaddr_in6);
	memset(addr_out, 0, sizeof(struct sockaddr_in6));
	#ifdef __WIN32
	const int len = recvfrom(sock->socket, (void*)output, maxlen, 0, (struct sockaddr*)addr_out, &socket_len);
	if (len == SOCKET_ERROR) {
		if (len == WSAEWOULDBLOCK) {
			return 0;
		} else {
			return -1;
		}
	}
	#else
	const int len = recvfrom(sock->socket, (void*)output, maxlen, MSG_DONTWAIT, (struct sockaddr*)addr_out, &socket_len);
	if (len == -1) {
		const int err = errno;
		if (err && err != EWOULDBLOCK) {
			return -1;
		}
		return 0;
	}
	#endif
	return len;
}

int nx_net_write(struct nx_net_socket *sock, const unsigned char *msg, const uint16_t len, const struct sockaddr_in6 *target) {
	#ifdef __WIN32
	const int success = sendto(sock->socket, (char*)msg, len, 0, (SOCKADDR*)target, sizeof(sockaddr_in6));
	if (success == SOCKET_ERROR) {
		const int err = WSAGetLastError();
		return -1;
	}
	#else
	const int success = sendto(sock->socket, (char*)msg, len, 0, (struct sockaddr*)target, sizeof(sockaddr_in6));
	if (success == -1 || !success) {
		const int err = errno;
		return -1;
	}
	#endif
	return success;
}

void nx_net_cleanup() {
	#ifdef __WIN32
	if (status) WSACleanup();
	#endif
	// nothing to do for linux xd
}