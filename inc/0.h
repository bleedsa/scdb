#ifndef __K12_INC_0_H__
#define __K12_INC_0_H__

#define Z(x) (sizeof(x))

using C = unsigned char;
using S = size_t;
using I = uint32_t;
using F = double;

#include <mem.h>

/** make a heap allocated buffer of T with x elements */
template<typename T>
inline static void *mk(size_t x) {
	return xalloc(sizeof(T) * x);
}

template<typename T>
inline static void *remk(void *buf, size_t x) {
	return xrealloc(buf, sizeof(T) * x);
}

#endif
