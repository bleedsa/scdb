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

auto static integer(tape_t *t) -> tok_t {
	char c;
	S i = t->i;
	for (c = t->peek(); c != 0 && isdigit(c); c = t->peek()) t->inc();
	return mktok(t, i, TOK_INT);
}

auto static name(tape_t *t) -> tok_t {
	char c;
	S i = t->i;
	for (c = t->peek(); c != 0 && isname(c); c = t->peek()) t->inc();
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

auto static single(tape_t *t, tokty_t ty) -> tok_t {
	S i = t->i;
	t->inc();
	return mktok(t, i, ty);
}

#define ERR(m){err.append(m); goto fail;}

auto lex(tape_t *t) -> Res<Vec<tok_t>> {
	str_t err;
	auto r = Vec<tok_t>();

	for (char c = t->peek(); c != 0; c = t->peek()) {
		Opt<tok_t> o;
		auto i = t->i;

		switch (c) {
		case '(':
		case '[':
		case '{':
			r.push(single(t, TOK_OPN));
			break;

		case ')':
		case ']':
		case '}':
			r.push(single(t, TOK_CLS));
			break;

		case ';':
			r.push(single(t, TOK_SEP));
			break;

		case '"':
			t->inc();
			o = string(t);
			if (o.is()) r.push(*o.un());
			else ERR("unclosed str");
			break;

		default:
			if (isdigit(c)) r.push(integer(t));
			else if (isalpha(c)) r.push(name(t));
			else {
				err.append("unrecognized char '");
				err.push(c);
				err.push('\'');
				goto fail;
			}
		}
	}

	if (r.i == 0) ERR("no tokens found");

	return Res<Vec<tok_t>>(r);
fail:
	return Res<Vec<tok_t>>(err);
}
