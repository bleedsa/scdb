#ifndef __K12_INC_T_H__
#define __K12_INC_T_H__

#include <0.h>

template<typename T>
struct Opt {
	T x;
	bool e;

	inline Opt() {
		e = false;
	}

	inline Opt(T t) {
		x = t, e = true;
	}

	~Opt() {}

	inline Opt(const Opt<T>& y) {
		x = y.x, e = y.e;
	}

	inline Opt<T>& operator=(const Opt<T>& y) {
		x = y.x, e = y.e;
		return *this;
	}

	inline auto un() -> T* {
		return &x;
	}
};

template<typename T>
inline static bool operator==(const Opt<T>& x, const Opt<T>& y) {
	return x.e == y.e ? x.x == y.x : false;
}

#endif
