#include <stdarg.h>

#include <vec.h>
#include <db.h>

/* delete all items in a matrix column */
template<typename T>
inline static auto mat_del_col(db::Mat *mat, S col) -> void {
	for (S r = 0; r < mat->H; r++) delete *mat->idx<T>(r, col);
}

db::Mat::Mat(A<db::val::ty> tys) : tys{tys} {
	auto s = chrZ(&tys);
	W = s.len(), H = 0, size = max<S>(&s), ptr = (C*)malloc(size);
}

db::Mat::~Mat() {
	S i = 0;
	/* delete all the columns if we need */
	tys.for_each([&](db::val::ty *ty){
		switch (*ty) {
		case val::AI: mat_del_col<A<I>*>(this, i); break;
		case val::AC: mat_del_col<A<C>*>(this, i); break;
		case val::AF: mat_del_col<A<F>*>(this, i); break;
		case val::AS: mat_del_col<A<S>*>(this, i); break;
		default:
		}
		i++;
	});
	free(ptr);
}

#include <stdio.h>

auto db::Mat::mkrow() -> void {
	H++;
	ptr = (C*)realloc(ptr, size * W * H);
}

db::NS::NS() {
	names = Vec<str_t>(), mats = Vec<Mat>();
}

db::NS::~NS() {}

auto db::NS::mk(str_t n, A<db::val::ty> t) -> void {
	names.push(n);
	mats.push(db::Mat(t));
}

db::Db::Db() {
	names = Vec<str_t>(), NSs = Vec<NS>();
}

db::Db::~Db() {}

auto db::Db::mkNS(str_t n) -> void {
	names.push(n);
	NSs.push(db::NS());
}

auto db::chrZ(A<db::val::ty> *x) -> A<S> {
	return x->each<unsigned long>([](db::val::ty *x) {
		switch (*x) {
		case db::val::I: return sizeof(I);
		case db::val::F: return sizeof(F);
		case db::val::S: return sizeof(S);
		case db::val::C: return sizeof(C);

		case db::val::AI: return sizeof(A<I>*);
		case db::val::AC: return sizeof(A<C>*);
		case db::val::AF: return sizeof(A<F>*);
		case db::val::AS: return sizeof(A<S>*);
		}
	});
}

