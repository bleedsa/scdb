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
};

#endif
