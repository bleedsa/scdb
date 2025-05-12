#include <string.h>
#include <stdio.h>

#include <0.h>
#include <mem.h>
#include <str.h>
#include <vec.h>
#include <p.h>

auto tok_t::to_str() -> str_t {
	auto r = str_t();
	for (S x = i; x < i + len; x++) r.push(src[x]);
	return r;
}

tape_t::tape_t(char *x) {
	len = strlen(x), i = 0, line = 1, col = 1;
	src = (char*)mk<char>(len);
	memcpy(src, x, Z(char) * len);
}

tape_t::~tape_t() {
	free(src);
}

static auto mktok(tape_t *t, S i, tokty_t ty) -> tok_t {
	return (tok_t){t->src, i, t->i - i, ty};
}

#define isname(c) (isalpha(c)||(c=='_'))

auto integer(tape_t *t) -> tok_t {
	char c;
	S i = t->i;
	for (c = t->peek(); c != 0 && isdigit(c); c = t->peek(), t->inc());
	return mktok(t, i, TOK_INT);
}

auto static name(tape_t *t) -> tok_t {
	char c;
	S i = t->i;
	for (c = t->peek(); c != 0 && isname(c); c = t->peek(), t->inc());
	return mktok(t, i, TOK_NAM);
}

auto static string(tape_t *t) -> Opt<tok_t> {
	char c;
	S i = t->i;
	for (c = t->peek(); c != 0 && c != '"'; c = t->peek()) t->inc();

	auto tok = mktok(t, i, TOK_STR);
	if (c == '"') t->inc();
	else goto none;

	return Opt<tok_t>(tok);
none:
	return Opt<tok_t>();
}

auto lex(tape_t *t) -> Opt<Vec<tok_t>> {
	auto r = Vec<tok_t>();

	for (
		char c = t->peek();
		c != 0;
		c = t->peek()
	) {
		Opt<tok_t> o;
		switch (c) {
		case '"':
			t->inc();
			o = string(t);
			if (o.is()) r.push(*o.un());
			else goto none;
			break;
		default:
			if (isdigit(c)) r.push(integer(t));
			else if (isalpha(c)) r.push(name(t));
			else goto none;
		}
	}

	if (r.i == 0) goto none;

	return Opt<Vec<tok_t>>(r);
none:
	return Opt<Vec<tok_t>>();
}
