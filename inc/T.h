#ifndef __K12_INC_T_H__
#define __K12_INC_T_H__

#include <0.h>

template<typename X, typename Y>
struct Ethr {
	union {
		X x;
		Y y;
	};
	bool e;

	inline Ethr(X x) : x{x}, e{true}  {}
	inline Ethr(Y y) : y{y}, e{false} {}
	inline ~Ethr() {}

	inline auto is() -> bool {
		return e;
	}

	inline auto un() -> X* {
		return &x;
	}

	inline auto err() -> Y* {
		return &y;
	}
};

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

	inline auto is() -> bool {
		return e;
	}
};

template<typename T>
inline static bool operator==(const Opt<T>& x, const Opt<T>& y) {
	return x.e == y.e ? x.x == y.x : false;
}

#endif
