#include <stdio.h>

#include <str.h>
#include <fs.h>
#include <p.h>

int main(int argc, char **argv) {
	str_t ln;
	printf("k12 repl * (c) skylar bleed 2025 * ? for help\n\n");

	do {
		putc(' ', stdout);
		fflush(stdout);
		ln = Freadln(stdin);

		auto s = ln.to_cstr();
		auto t = tape_t(s);
		auto o = lex(&t);
		if (o != Opt<Vec<tok_t>>()) {
			auto toks = o.un();
			for (S i = 0; i < toks->i; i++) {
				auto tok = toks->at(i);
				auto tokS = tok->to_str().to_cstr();
				printf("%s\n", tokS);
				free(tokS);
			}
		} else printf("'lex\n");

		free(s);
	} while (true);

	return 0;
}
