#include <stdio.h>

#include <vec.h>
#include <db.h>

/* delete all items in a matrix column */
template<typename T>
inline static auto mat_del_col(db::Mat *mat, S col) -> void {
	for (S r = 0; r < mat->H; r++) delete *mat->idx<T>(r, col);
}

db::Mat::Mat(A<db::val::ty> tys) : tys{tys} {
	auto s = chrZ(&tys);
	W = s.len(), H = 0, size = max<S>(&s);
}

db::Mat::~Mat() {
	S i = 0;
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
//	if (ptr != nullptr) free(ptr);
}

#define CLONE(x) { \
	W = x.W, H = x.H, size = x.size; \
	if (x.ptr != nullptr) { \
		ptr = (C*)xalloc(size * W * H); \
		for (S r = 0; r < H; r++) { \
			for (S c = 0; c < W; c++) { \
				switch (*tys.at(c)) { \
				CASE(val::I,*idx_<I>(r, c) = *x.idx_<I>(r, c)) \
				CASE(val::F,*idx_<F>(r, c) = *x.idx_<F>(r, c)) \
				CASE(val::C,*idx_<C>(r, c) = *x.idx_<C>(r, c)) \
				CASE(val::S,*idx_<S>(r, c) = *x.idx_<S>(r, c)) \
				CASE(val::AI,**idx_<A<I>*>(r, c) = **x.idx_<A<I>*>(r, c)) \
				CASE(val::AF,**idx_<A<F>*>(r, c) = **x.idx_<A<F>*>(r, c)) \
				CASE(val::AC,**idx_<A<C>*>(r, c) = **x.idx_<A<C>*>(r, c)) \
				CASE(val::AS,**idx_<A<S>*>(r, c) = **x.idx_<A<S>*>(r, c)) \
				} \
			} \
		} \
	} \
}

db::Mat::Mat(const db::Mat& x) : tys{x.tys} CLONE(x)
const db::Mat& db::Mat::operator=(const db::Mat& x) {
	tys = x.tys;
	CLONE(x);
	return *this;
}

auto db::Mat::mkrow() -> void {
	H++;
	ptr = ptr == nullptr
		? (C*)xalloc(size * W * H)
		: (C*)xrealloc(ptr, size * W * H);
}

db::NS::NS() {
	names = Vec<str_t>(), mats = Vec<Mat>();
}

db::NS::~NS() {}

auto db::NS::mk(str_t n, A<db::val::ty> t) -> void {
	names.push(n);
	auto m = db::Mat(t);
	mats.push(m);
}

auto db::NS::fnd(str_t *n) -> Mat* {
	for (S i = 0; i < len(); i++) if (n->eq(names.at(i))) return mats.at(i);
	return nullptr;
}

db::Db::Db() {
	names = Vec<str_t>(), NSs = Vec<NS>();
}

db::Db::~Db() {}

auto db::Db::mkNS(str_t n) -> void {
	names.push(n);
	NSs.push(db::NS());
}

auto db::Db::fnd(str_t *n) -> NS* {
	for (S i = 0; i < len(); i++) if (n->eq(names.at(i))) return NSs.at(i);
	return nullptr;
}

auto db::chrZ(A<db::val::ty> *x) -> A<S> {
	return x->each<unsigned long>([](db::val::ty *x) {
		switch (*x) {
		case db::val::I: return sizeof(I);
		case db::val::C: return sizeof(C);
		case db::val::F: return sizeof(F);
		case db::val::S: return sizeof(S);

		case db::val::AI: return sizeof(A<I>*);
		case db::val::AC: return sizeof(A<C>*);
		case db::val::AF: return sizeof(A<F>*);
		case db::val::AS: return sizeof(A<S>*);
		}
	});
}

