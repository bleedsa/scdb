#include <stdio.h>

#include <str.h>
#include <fs.h>

int main(int argc, char **argv) {
	str_t ln;
	printf("k12 repl * (c) skylar bleed 2025 * ? for help\n\n");

	do {
		putc(' ', stdout);
		ln = Freadln(stdin);
		auto s = ln.to_cstr();
		printf("%s\n", s);
		free(s);
	} while (true);

	return 0;
}
