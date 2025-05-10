#ifndef __K12_INC_STR_H__
#define __K12_INC_STR_H__

#include <ctype.h>

#include <0.h>

struct str_t {
	C *buf;
	size_t i;
	size_t cap;

	str_t();
	~str_t();

	str_t(const str_t& x);
	str_t& operator=(const str_t& x);

	void resize(size_t x);
	void push(C x);
	void append(const char *x);

	inline C at(size_t x) {
		return buf[x];
	}
};

#endif
