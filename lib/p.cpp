#include <string.h>

#include <0.h>
#include <mem.h>
#include <str.h>
#include <p.h>

auto tok_t::to_str() -> str_t {
	auto r = str_t();
	for (S i = this->i; i < this->i + len; i++) r.push(src[i]);
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

/*
 * toks:
 * {
 * 	src
 * 	i
 * 	len
 * 	ty
 * }
 */

static auto mktok(tape_t *t, S i, tokty_t ty) -> tok_t {
	return (tok_t){t->src, i, t->i - i, ty};
}

auto integer(tape_t *t) -> tok_t {
	char c;
	S i = t->i;
	for (
		c = t->peek();
		c != 0 && isdigit(c);
		c = t->peek(), t->inc()
	);
	return mktok(t, i, TOK_INT);
}
