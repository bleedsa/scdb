#ifndef __K12_INC_STR_H__
#define __K12_INC_STR_H__

#include <stdlib.h>
#include <ctype.h>

#include <0.h>
#include <mem.h>

namespace str {
	inline static S len(C *x) {S i; for (i = 0; *x; x++, i++); return i;}
}

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

	inline char *to_cstr() {
		char *s = (char*)mk<char>(i + 1);
		xcpy<char>(s, (char*)buf, i);
		s[i] = 0;
		return s;
	}
};

template<typename T>
using Res = Ethr<T, str_t>;

#endif
