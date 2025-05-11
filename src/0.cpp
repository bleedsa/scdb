#include <stdio.h>

#include <str.h>
#include <fs.h>
#include <p.h>

int main(int argc, char **argv) {
	str_t ln;
	printf("k12 repl * (c) skylar bleed 2025 * ? for help\n\n");

	do {
		char c;
		auto ln = str_t();
		for (c = getchar(); c != '\n'; c = getchar()) {
			if (c == EOF) goto ret;
			ln.push(c);
		}

		auto s = ln.to_cstr();
		auto t = tape_t(s);
		auto o = lex(&t);

		if (o != Opt<Vec<tok_t>>()) {
			auto toks = o.un();
			for (S i = 0; i < toks->i; i++) {
				auto tok = toks->at(i);
				auto tokS = tok->to_str();
				auto tokC = tokS.to_cstr();
				printf("%s ", tokC);
				free(tokC);
			}
			printf("\n");
		} else printf("'lex\n");

		free(s);
	} while (true);

ret:
	return 0;
}
