#include "vector.h"
#include "string.h"

#ifndef term_h
#define term_h

namespace core
{

struct term
{
	term();
	term(double co, int x, int y, int z, int w);
	term(string s);
	~term();

	double coeff;
	int a, b, c, d;

	term &operator=(term t);
	term &operator*=(term t);
	term &operator/=(term t);

	template <class type>
	type operator()(type x, type y, type z, type w)
	{
		return coeff * fast_pow(x, a) * fast_pow(y, b) *
					   fast_pow(z, c) * fast_pow(w, d);
	}

	template <class type>
	type operator()(vector<type, 4> f)
	{
		return coeff * fast_pow(f[0], a) * fast_pow(f[1], b) *
					   fast_pow(f[2], c) * fast_pow(f[3], d);
	}

	term exp(int e);
	int degree();
};

file &operator<<(file &os, term t);

term operator-(term t);

term operator*(term t1, term t2);
term operator*(double d, term t);
term operator*(term t, double d);

term operator/(term t1, term t2);
term operator/(double d, term t);
term operator/(term t, double d);

bool operator<(term t1, term t2);
bool operator>(term t1, term t2);
bool operator==(term t1, term t2);

}

#endif
