#include <stdlib.h>
#include <string.h>

#include <0.h>
#include <str.h>
#include <mem.h>

str_t::str_t() {
	i = 0, cap = 8, buf = (C*)mk<C>(cap);
}

str_t::~str_t() {
	i = 0, cap = 0;
	free(buf);
}

void str_t::resize(size_t x) {
	cap = x, buf = (C*)remk<C>(buf, cap);
}

void str_t::push(C x) {
	if (i >= cap) resize(cap * 2);
	buf[i++] = x;
}

void str_t::append(const char *x) {
	for (size_t i = 0; i < strlen(x); i++) push(x[i]);
}
