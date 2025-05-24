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

	/* allocate some strings */
	str_t test = str_t("test"), foo = str_t("foo"), bar = str_t("bar");
	/* make a new database and make a namespace */
	auto D = db::Db();
	D.mkNS(test);

	auto TEST = D.fnd(&test);
	TEST->mk(foo, tys);
	TEST->mk(bar, tys);

	auto FOO = TEST->fnd(&foo);
	for (S i = 0; i < 3; i++) {
		FOO->mkrow();
		FOO->setA<I>(i, 0, ai);
		*FOO->idx<F>(i, 1) = i + 0.1;
	}

	auto s = fmt::Db(&D);
	auto sC = s.to_cstr();
	printf("db:\n%s\n", sC);
	free(sC);

	return 0;
}
