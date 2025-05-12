#include <stdio.h>

#include <str.h>
#include <fs.h>
#include <p.h>

int main(int argc, char **argv) {
	printf("stone cold database repl | (c) skylar bleed 2025\n\n");

	do {
		char c;
		auto ln = str_t();

		PUTC(' ');
		for (c = getchar(); c != '\n'; c = getchar()) {
			if (c == EOF) goto ret;
			ln.push(c);
		}

		auto s = ln.to_cstr();
		auto t = tape_t(s);
		auto o = lex(&t);

		if (o != Opt<Vec<tok_t>>()) {
			auto toks = o.un();
			for (S i = 0; i < toks->len(); i++) {
				auto tok = toks->at(i);
				auto tokS = tok->to_str();
				auto tokC = tokS.to_cstr();
				printf("%s ", tokC);
				free(tokC);
			}
			PUTC('\n');
		} else printf("'lex\n");

		free(s);
	} while (true);

ret:
	return 0;
}
