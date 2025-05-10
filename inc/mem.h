#ifndef __K12_INC_MEM_H__
#define __K12_INC_MEM_H__

#include <0.h>

void *xalloc(S x);
void *xrealloc(void *buf, S x);

/* make a heap allocated buffer of T with x elements */
template<typename T>
inline static T *mk(size_t x) {
	return (T*)xalloc(Z(T) * x);
}

/* realloc a heap allocated buffer with x elements */
template<typename T>
inline static T *remk(void *buf, size_t x) {
	return (T*)xrealloc(buf, Z(T) * x);
}

/* copy a buffer into another */
template<typename T>
inline static void xcpy(T *dst, T *src, S z) {
	memcpy(dst, src, Z(T) * z);
}

#endif
