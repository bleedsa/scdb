#ifndef __SCDB_INC_DB_H__
#define __SCDB_INC_DB_H__

#include <str.h>
#include <vec.h>

namespace db {
	/* a ragged matrix */
	struct Mat {
		size_t W;
		size_t H;
		size_t size;
		uint8_t *ptr;

		Mat(A<size_t> s);
		~Mat();

		void mkrow();

		template<typename T>
		inline T *nth(size_t r, size_t n) {
			return (T*)(ptr + (size * (r * W + n)));
		}

		template<typename T>
		inline void set(size_t r, size_t n, T x) {
			*(T*)(ptr + (size * (r * W + n))) = x;
		}
	};

	/* namespace */
	struct NS {
		Vec<str_t> names;
		Vec<Mat> mats;

		NS();
		~NS();

		void mk(str_t n, A<C> t);
	};

	struct Db {
	
	};

	namespace val {
		enum ty {
			I = 'i',
			C = 'c',
			F = 'f',
			S = 's',
		};
	};

	/* get the size of types */
	A<size_t> chrZ(A<val::ty> *x);
}

#endif
