#include <stdio.h>

#include <db.h>
#include <fmt.h>

int main(int argc, char **argv) {
	auto tys = A<db::val::ty>(3);
	tys.set(0, db::val::I);
	tys.set(1, db::val::S);
	tys.set(2, db::val::AC);

	auto h = str::to_AC("hello");

	auto M = db::Mat(tys);
	for (size_t i = 0; i < 2; i++) {
		M.mkrow();
		M.set<int32_t>(i, 0, 32);
		M.set<uint64_t>(i, 1, 55);
		M.set<A<C>*>(i, 2, new A<C>(3));
		auto a = *M.idx<A<C>*>(i, 2);
		*a = h;

		printf("%d\n", *M.idx<int32_t>(i, 0));
		printf("%zu\n", *M.idx<uint64_t>(i, 1));
		auto c = str::from_AC(*M.idx<A<C>*>(i, 2));
		printf("%s\n", c);
		free(c);
	}

	tys = A<db::val::ty>(2);
	tys.set(0, db::val::AI);
	tys.set(1, db::val::AF);

	auto ai = A<I>(3);
	ai.set(0, 1);
	ai.set(1, 2);
	ai.set(2, 3);

	auto af = A<F>(2);
	af.set(0, 1.2);
	af.set(1, 5.6);

	auto M1 = db::Mat(tys);
	for (S i = 0; i < 3; i++) {
		M1.mkrow();
		M1.set<A<I>*>(i, 0, new A<I>(2));
		**M1.idx<A<I>*>(i, 0) = ai;
		M1.set<A<F>*>(i, 1, new A<F>(2));
		**M1.idx<A<F>*>(i, 1) = af;
	}
	for (S r = 0; r < 3; r++) {
		auto i = *M1.idx<A<I>*>(r, 0);
		i->for_each([](I *x){ printf("%d ", *x); });
		printf("\n");
		auto f = *M1.idx<A<F>*>(r, 1);
		f->for_each([](F *x){ printf("%f ", *x); });
		printf("\n");
	}

	auto M1F = fmt::Mat(&M1);
	auto M1C = M1F.to_cstr();
	printf("M1:\n%s\n", M1C);
	free(M1C);

	auto D = db::Db();
	D.mkNS("hello");

	auto s = fmt::Db(&D);
	auto sC = s.to_cstr();
	printf("db:\n%s\n", sC);
	free(sC);

	return 0;
}
