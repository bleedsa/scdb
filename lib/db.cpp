#include <stdarg.h>

#include <vec.h>
#include <db.h>

db::mat_t::mat_t(A<size_t> s) : size{0} {
	auto len = s.len();
	for (size_t i = 0; i < len; i++) {
		auto x = s.at(i);
		size = *x > size ? *x : size;
	}

	ptr = (uint8_t*)malloc(size * len);
}

db::mat_t::~mat_t() {
	free(ptr);
}
