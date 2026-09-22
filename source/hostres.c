/*
 * hostres.c: hostname resolution using getaddrinfo()
 *
 * Replaces deprecated gethostbyname() with IPv6-compatible getaddrinfo()
 * This file exists to provide resolve_hostname() to all build targets.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_foobar
{
	union {
		struct sockaddr_in sin;
#ifdef IPV6
		struct sockaddr_in6 sin6;
#endif
	} sins;
};

#define sf_family sins.sin.sin_family
#define sf_port sins.sin.sin_port
#define sf_addr sins.sin.sin_addr
#ifdef IPV6
#define sf_addr6 sins.sin6.sin6_addr
#endif

int resolve_hostname(const char *host, struct sockaddr_foobar *result)
{
	struct addrinfo hints, *res;
	int ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(host, NULL, &hints, &res);
	if (ret != 0 || !res)
		return -1;

	if (res->ai_family == AF_INET) {
		struct sockaddr_in *sin = (struct sockaddr_in *)res->ai_addr;
		memcpy(&result->sf_addr, &sin->sin_addr, sizeof(struct in_addr));
		result->sf_family = AF_INET;
	}
	freeaddrinfo(res);
	return 0;
}
