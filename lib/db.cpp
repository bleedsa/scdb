#include <stdarg.h>

#include <vec.h>
#include <db.h>

db::Mat::Mat(A<size_t> s) {
	W = s.len(), H = 0, size = max<size_t>(&s);
	ptr = (uint8_t*)malloc(size);
}

db::Mat::~Mat() {
	free(ptr);
}

auto db::Mat::mkrow() -> void {
	H++;
	ptr = (uint8_t*)realloc(ptr, size * W * H);
}

auto db::chrZ(A<db::val::ty> *x) -> A<size_t> {
	return x->each<unsigned long>([](db::val::ty *x) {
		switch (*x) {
		case db::val::I: return sizeof(int32_t);
		case db::val::S: return sizeof(size_t);
		case db::val::C: return sizeof(uint8_t);

		default:
			return (unsigned long)0;
		}
	});
}
