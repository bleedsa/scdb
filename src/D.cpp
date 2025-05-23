#include <stdio.h>

#include <db.h>
#include <fmt.h>

int main(int argc, char **argv) {
	auto ai = A<I>(3);
	ai.set(0, 1);
	ai.set(1, 2);
	ai.set(2, 3);

	auto af = A<F>(2);
	af.set(0, 1.2);
	af.set(1, 5.6);

	auto tys = A<db::val::ty>(2);
	tys.set(0, db::val::AI);
	tys.set(1, db::val::F);

	auto chr = A<db::val::ty>(2);
	chr.set(0, db::val::I);
	chr.set(1, db::val::AC);

	/* allocate some strings */
	str_t test = str_t("test"), fooS = str_t("foo"), barS = str_t("bar");
	/* make a new database and make a namespace */
	auto D = db::Db();
	D.mkNS(test);

	auto TEST = D.fnd(&test);
	TEST->mk(fooS, tys);
	TEST->mk(barS, chr);

	auto foo = TEST->fnd(&fooS);
	for (S i = 0; i < 3; i++) {
		foo->mkrow();
		foo->setA<I>(i, 0, ai);
		foo->set<F>(i, 1, i + (i / 1));
	}

	auto bar = TEST->fnd(&barS);
	const char *strs[] = {"foo", "bar", "baz"};
	for (S i = 0; i < 3; i++) {
		bar->mkrow();
		bar->set<I>(i, 0, i);
		bar->setA<C>(i, 1, str::to_AC(strs[i]));
	}

	auto s = fmt::Db(&D);
	auto sC = s.to_cstr();
	printf("db:\n%s\n", sC);
	free(sC);

	return 0;
}
