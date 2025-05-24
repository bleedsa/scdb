#ifndef __SCDB_INC_FMT_H__
#define __SCDB_INC_FMT_H__

#include <str.h>
#include <db.h>

namespace fmt {
	str_t fmtF(F *x);
	str_t fmtI(I *x);
	str_t fmtS(S *x);

	str_t AC(A<C> *x);
	str_t AI(A<I> *x);
	str_t AF(A<F> *x);
	str_t AS(A<S> *x);

	str_t Mat(db::Mat *x);
	str_t Mat(S pad, db::Mat *x);
	str_t NS(db::NS *x);
	str_t Db(db::Db *x);
};

#endif
