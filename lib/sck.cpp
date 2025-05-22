#include <sck.h>

#include <sys/socket.h>

auto sck::open(str_t path) -> int {
	int s = socket(AF_UNIX, SOCK_STREAM, 0);
	if (s == -1) return -1;

	return s;
}
