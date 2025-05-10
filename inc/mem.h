#ifndef __K12_INC_MEM_H__
#define __K12_INC_MEM_H__

#include <0.h>

void *xalloc(S x);
void *xrealloc(void *buf, S x);

/* make a heap allocated buffer of T with x elements */
template<typename T>
inline static void *mk(size_t x) {
	return xalloc(Z(T) * x);
}

/* realloc a heap allocated buffer with x elements */
template<typename T>
inline static void *remk(void *buf, size_t x) {
	return xrealloc(buf, Z(T) * x);
}

#endif
