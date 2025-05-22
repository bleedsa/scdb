#include <stdio.h>

#include <db.h>

int main(int argc, char **argv) {
	auto s = A<db::val::ty>(3);
	s.set(0, db::val::I);
	s.set(1, db::val::S);
	s.set(2, db::val::C);
	auto z = db::chrZ(&s);

	auto M = db::Mat(z);
	for (size_t i = 0; i < 2; i++) {
		M.mkrow();
		M.set<int32_t>(i, 0, 32);
		M.set<uint64_t>(i, 1, 55);
		M.set<uint8_t>(i, 2, 'A');
		printf("%d\n", *M.nth<int32_t>(i, 0));
		printf("%zu\n", *M.nth<uint64_t>(i, 1));
		printf("%c\n", *M.nth<uint8_t>(i, 2));
	}

	return 0;
}
