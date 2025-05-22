#ifndef __K12_INC_VEC_H__
#define __K12_INC_VEC_H__

#include <stdlib.h>

#include <0.h>
#include <mem.h>

/* a vector with a static length */
template<typename T>
struct A {
	S cap;
	T *buf;

	A(S len) : cap{len} {
		buf = mk<T>(cap);
	}

	~A() {
		free(buf);
	}

	#define CLONEA(x) { \
		cap = x.cap, buf = mk<T>(cap); \
		xcpy<T>(buf, x.buf, cap); \
	}

	inline A(const A<T>& x) CLONEA(x);

	inline A<T>& operator=(const A<T>& x) {
		CLONEA(x);
		return *this;
	}

	inline auto len() -> S {
		return cap;
	}

	inline auto at(S i) -> T* {
		return &buf[i];
	}

	inline auto set(S i, T x) -> void {
		buf[i] = x;
	}

	template<typename U, typename F>
	auto each(F f) -> A<U> {
		auto z = len();
		auto r = A<U>(z);
		for (S i = 0; i < z; i++) r.buf[i] = f(&buf[i]);
		return r;
	}

	template<typename F>
	auto for_each(F f) -> void {
		for (S i = 0; i < cap; i++) f(&buf[i]);
	}
};

template<typename T>
struct Vec {
	T *buf;
	S i;
	S cap;

	Vec() {
		i = 0, cap = 8;
		buf = mk<T>(cap);
	}

	~Vec() {
		i = 0, cap = 0;
		free(buf);
	}

	#define CLONEVEC(x) { \
		i = x.i, cap = x.cap; \
		buf = mk<T>(cap); \
		xcpy(buf, x.buf, cap); \
	}

	inline Vec(const Vec<T>& x) CLONEVEC(x);

	inline Vec<T>& operator=(const Vec<T>& x) {
		CLONEVEC(x);
		return *this;
	}

	inline S len() {
		return i;
	}

	void resize(S x) {
		cap = x, buf = remk<T>(buf, cap);
	}

	void push(T x) {
		if (i >= cap) resize(cap * 2);
		buf[i++] = x;
	}

	inline T *at(S x) {
		return &buf[x];
	}
};

template<typename T>
inline bool operator==(const Vec<T>& x, const Vec<T>& y) {
	if (x.i == y.i) {
		for (S i = 0; i < x.i; i++) {
			if (x.buf[i] != y.buf[i]) return false;
		}
		return true;
	} else {
		return false;
	}
}

template<typename T>
inline auto max(A<T> *x) -> T {
	T r = 0;
	x->for_each([&](T *x){r = *x > r ? *x : r;});
	return r;
}

#endif
