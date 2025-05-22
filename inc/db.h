#ifndef __SCDB_INC_DB_H__
#define __SCDB_INC_DB_H__

#include <vec.h>

namespace db {
	struct mat_t {
		size_t coln;
		size_t size;
		uint8_t *ptr;

		mat_t(A<size_t> s);
		~mat_t();

		template<typename T>
		inline T *nth(size_t n) {
			return (T*)(ptr + (n * size));
		}

		template<typename T>
		inline void set(size_t n, T x) {
			*(T*)(ptr + (n * size)) = x;
		}
	};

	struct ns_t {
	
	};

	struct Db {
	
	};
}

#endif
