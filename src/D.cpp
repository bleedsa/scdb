#include <stdio.h>

#include <db.h>

int main(int argc, char **argv) {
	auto s = A<size_t>(3);
	s.set(0, sizeof(int32_t));
	s.set(0, sizeof(uint64_t));
	s.set(0, sizeof(uint8_t));

	auto M = db::mat_t(s);
	M.set(2, 'A');
	printf("%c\n", *M.nth<uint8_t>(2));

	return 0;
}
