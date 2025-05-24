#include <stdio.h>

#include <0.h>
#include <str.h>
#include <fmt.h>

auto fmt::fmtI(I *x) -> str_t {
	char *a;
	auto r = str_t();
	asprintf(&a, "%d", *x);
	r.append(a);
	free(a);
	return r;
}

auto fmt::fmtF(F *x) -> str_t {
	char *a;
	auto r = str_t();
	asprintf(&a, "%f", *x);
	r.append(a);
	free(a);
	return r;
}

auto fmt::fmtS(S *x) -> str_t {
	char *a;
	auto r = str_t();
	asprintf(&a, "%zu", *x);
	r.append(a);
	free(a);
	return r;
}

auto fmt::AC(A<C> *x) -> str_t {
	auto r = str_t();
	r.push('"');
	auto a = str::from_AC(x);
	r.append(a);
	r.push('"');
	return r;
}

const C SEP = ' ';

auto fmt::AI(A<I> *x) -> str_t {
	auto r = str_t();
	x->for_each([&](I *i) {
		auto s = fmt::fmtI(i);
		r.append(&s);
		r.push(SEP);
	});
	r.back();
	return r;
}

auto fmt::AF(A<F> *x) -> str_t {
	auto r = str_t();
	x->for_each([&](F *f) {
		auto s = fmt::fmtF(f);
		r.append(&s);
		r.push(SEP);
	});
	r.back();
	return r;
}

auto fmt::AS(A<S> *x) -> str_t {
	auto r = str_t();
	x->for_each([&](S *s) {
		auto q = fmt::fmtS(s);
		r.append(&q);
		r.push(SEP);
	});
	r.back();
	return r;
}

auto fmt::Mat(S pad, db::Mat *x) -> str_t {
	auto ret = str_t();

	for (S r = 0; r < x->H; r++) {
		for (S i = 0; i < pad; i++) ret.push(' ');
		ret.append(" ; ");
		for (S c = 0; c < x->W; c++) {
			str_t f;
			switch (*x->tys.at(c)) {
				CASE(db::val::I, f = fmt::fmtI(x->idx<I>(r, c)))
				CASE(db::val::F, f = fmt::fmtF(x->idx<F>(r, c)))
				CASE(db::val::C, f.push(*x->idx<C>(r, c)))
				CASE(db::val::S, f = fmt::fmtS(x->idx<S>(r, c)))

				CASE(db::val::AC, f = fmt::AC(*x->idx<A<C>*>(r, c)))
				CASE(db::val::AI, f = fmt::AI(*x->idx<A<I>*>(r, c)))
				CASE(db::val::AF, f = fmt::AF(*x->idx<A<F>*>(r, c)))
				CASE(db::val::AS, f = fmt::AS(*x->idx<A<S>*>(r, c)))
			}
			ret.append(&f);
			ret.push('|');
		}
		ret.back();
		ret.push('\n');
	}

	return ret;
}

auto fmt::NS(db::NS *x) -> str_t {
	auto r = str_t();
	for (S i = 0; i < x->len(); i++) {
		auto s = x->names.at(i);
		auto len = s->len();
		r.append(s); r.append(":{\n");
		auto m = fmt::Mat(len, x->mats.at(i));
		r.append(&m);
		for (S j = 0; j < len; j++) r.push(' ');
		r.append(" }\n");
	}
	return r;
}

auto fmt::Db(db::Db *x) -> str_t {
	auto r = str_t();
	for (S i = 0; i < x->len(); i++) {
		auto s = x->names.at(i);
		r.append(s); r.push('\n');
		for (S j = 0; j < s->len(); j++) r.push('='); r.push('\n');
		auto n = fmt::NS(x->NSs.at(i));
		r.append(&n); r.push('\n');
	}
	return r;
}
