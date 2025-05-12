#include <stdlib.h>
#include <string.h>

#include <0.h>
#include <str.h>
#include <mem.h>

str_t::str_t() {
	i = 0, cap = 8, buf = (C*)mk<C>(cap);
}

str_t::str_t(const char *x) {
	*this = str_t();
	append(x);
}

str_t::~str_t() {
	i = 0, cap = 0;
	free(buf);
}

#define CLONE(x) { \
	i = x.i, cap = x.cap; \
	buf = (C*)mk<C>(cap); \
	memcpy(buf, x.buf, Z(C) * cap); \
}

str_t::str_t(const str_t& x) CLONE(x);

str_t& str_t::operator=(const str_t& x) {
	CLONE(x);
	return *this;
}

void str_t::resize(S x) {
	cap = x, buf = (C*)remk<C>(buf, cap);
}

void str_t::push(C x) {
	IF(i >= cap, resize(cap * 2));
	buf[i++] = x;
}

void str_t::append(const char *x) {
	for (S i = 0; i < strlen(x); i++) push(x[i]);
}

bool str_t::has(C x) {
	for (S j = 0; j < i; j++) if (buf[j] == x) return true;
	return false;
}
