#include <stdio.h>

#include <str.h>

int main(int argc, char **argv) {
	auto x = str_t();
	x.append("hello worldkamsdkmakldmaksdnakndklasnlanfklsndkn");

	printf("buf: %s, i: %d, cap: %d\n", x.buf, x.i, x.cap);

	return 0;
}
