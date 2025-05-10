#include <0.h>
#include <mem.h>

#include <stdlib.h>

void *xalloc(S x) {
	void *ptr = malloc(x);
	if (ptr == nullptr) exit(-1);
	memset(ptr, 0, x);
	return ptr;
}

void *xrealloc(void *buf, S x) {
	void *ptr = realloc(buf, x);
	if (ptr == nullptr) exit(-1);
	return ptr;
}
