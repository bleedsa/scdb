#ifndef __K12_INC_VEC_H__
#define __K12_INC_VEC_H__

template<typename T>
struct Vec {
	T *buf;
	S i;
	S cap;

	Vec() {
		i = 0, cap = 8;
		buf = mk<T>(cap);
	}

	~Vec() {
		i = 0, cap = 0;
		free(buf);
	}

	#define CLONEVEC(x) { \
		i = x.i, cap = x.cap; \
		buf = mk<T>(cap); \
		xcpy(buf, x.buf, cap); \
	}

	inline Vec(const Vec<T>& x) CLONEVEC(x);

	inline Vec<T>& operator=(const Vec<T>& x) {
		CLONEVEC(x);
		return *this;
	}

	inline S len() {
		return i;
	}

	void resize(S x) {
		cap = x, buf = remk<T>(buf, cap);
	}

	void push(T x) {
		if (i >= cap) resize(cap * 2);
		buf[i++] = x;
	}

	inline T *at(S x) {
		return &buf[x];
	}
};

template<typename T>
inline bool operator==(const Vec<T>& x, const Vec<T>& y) {
	if (x.i == y.i) {
		for (S i = 0; i < x.i; i++) {
			if (x.buf[i] != y.buf[i]) return false;
		}
		return true;
	} else {
		return false;
	}
}

#endif
