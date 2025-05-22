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
		/* the types of each column */
		A<val::ty> tys;
		/* matrix width */
		S W;
		/* matrix height */
		S H;
		/* the size of each aligned object */
		S size;
		/* a long block of memory that we index */
		C *ptr;

		Mat(A<val::ty> s);
		~Mat();

		void mkrow();

		/* index row r column n */
		template<typename T>
		inline T *idx(S r, S n) {
			return (T*)(ptr + (size * (r * W + n)));
		}

		/* set row r column n to x */
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
