#include <stdio.h>

#include <fs.h>
#include <str.h>

str_t readF(char *path) {
	auto r = str_t();
	auto f = fopen(path, "r");

	for (C c = fgetc(f); c != EOF; c = fgetc(f)) r.push(c);
	fclose(f);

	return r;
}

str_t Freadln(FILE *f) {
	auto r = str_t();
	for (C c = fgetc(f); c != '\n'; c = fgetc(f)) r.push(c);
	return r;
}
