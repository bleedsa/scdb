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
		auto tok = integer(&t);
		auto t_s = tok.to_str().to_cstr();
		printf("i: %d, len: %d: %s\n", tok.i, tok.len, t_s);

		free(s); free(t_s);
	} while (true);

	return 0;
}
