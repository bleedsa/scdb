#ifndef __K12_INC_P_H__

#include <ctype.h>

#include <0.h>
#include <vec.h>

enum tokty_t {
	TOK_INT,
	TOK_FLT,
	TOK_STR,
	TOK_OPN,
	TOK_CLS,
	TOK_NAM,
	TOK_VRB,
	TOK_SEP,
};

struct tok_t {
	char *src;
	S i;
	S len;
	tokty_t ty;

	str_t to_str();
};

inline static bool operator==(const tok_t& x, const tok_t& y) {
	return (x.i == y.i) && (x.len == y.len) && (x.ty == y.ty);
}

/* never copy this */
struct tape_t {
	char *src;
	S i;
	S len;
	S line;
	S col;

	tape_t(char *x);
	~tape_t();

	inline char peek() {
		return i < len ? src[i] : 0;
	}

	inline void inc() {
		i++, col++;
	}
};

Res<Vec<tok_t>> lex(tape_t *t);

#endif
