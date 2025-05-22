#ifndef __SCDB_INC_DB_H__
#define __SCDB_INC_DB_H__

#include <str.h>
#include <vec.h>

namespace db {
	namespace val {
		enum ty {
			I = 'i',
			C = 'c',
			F = 'f',
			S = 's',
			AI = 'I',
			AC = 'C',
			AF = 'F',
			AS = 'S',
		};
	};

	/* a ragged matrix */
	struct Mat {
		A<val::ty> tys;
		S W;
		S H;
		S size;
		C *ptr;

		Mat(A<val::ty> s);
		~Mat();

		void mkrow();

		template<typename T>
		inline T *nth(S r, S n) {
			return (T*)(ptr + (size * (r * W + n)));
		}

		template<typename T>
		inline void set(S r, S n, T x) {
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

	/* get the size of types */
	A<S> chrZ(A<val::ty> *x);
}

#endif
