#include <stdio.h>

#include <str.h>

int main(int argc, char **argv) {
	auto x = str_t();
	x.append("hello worldkamsdkmakldmaksdnakndklasnlanfklsndkn");
	auto y = x;

	printf("buf: %s, i: %d, cap: %d\n", y.buf, y.i, y.cap);

	return 0;
}
