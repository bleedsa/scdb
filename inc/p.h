#ifndef __K12_INC_P_H__

#include <ctype.h>

#include <0.h>

enum tokty_t {
	TOK_INT,
	TOK_FLT,
	TOK_STR,
	TOK_OPN,
	TOK_CLS,
	TOK_NAM,
};

struct tok_t {
	char *src;
	S i;
	S len;
	tokty_t ty;

	str_t to_str();
};

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

tok_t integer(tape_t *t);

#endif
