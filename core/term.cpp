/*
 * term.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: nbingham
 */

#include "term.h"

namespace core
{

term::term()
{
	coeff = 0.0;
	a = 0;
	b = 0;
	c = 0;
	d = 0;
}

term::term(double co, int x, int y, int z, int w)
{
	coeff = co;
	a = x;
	b = y;
	c = z;
	d = w;
}

term::term(string s)
{
	int x = s.find_first_of("x");
	int y = s.find_first_of("y");
	int z = s.find_first_of("z");
	int w = s.find_first_of("w");

	coeff = s.substr(0, x).to_double();
	a = s.substr(x+1, y-x-1).to_long();
	b = s.substr(y+1, z-y-1).to_long();
	c = s.substr(z+1, w-z-1).to_long();
	d = s.substr(w+1).to_long();
}

term::~term()
{
}

term &term::operator=(term t)
{
	coeff = t.coeff;
	a = t.a;
	b = t.b;
	c = t.c;
	d = t.d;
	return *this;
}

term &term::operator*=(term t)
{
	coeff *= t.coeff;
	a += t.a;
	b += t.b;
	c += t.c;
	d += t.d;
	return *this;
}

term &term::operator/=(term t)
{
	coeff /= t.coeff;
	a -= t.a;
	b -= t.b;
	c -= t.c;
	d -= t.d;
	return *this;
}

term term::exp(int e)
{
	term result;
	result.coeff = powi(coeff, e);
	result.a = a * e;
	result.b = b * e;
	result.c = c * e;
	result.d = d * e;
	return result;
}

int term::degree()
{
	int deg = 0x80000000;
	deg = a > deg ? a : deg;
	deg = b > deg ? b : deg;
	deg = c > deg ? c : deg;
	deg = d > deg ? d : deg;
	return deg;
}

file &operator<<(file &fout, term t)
{
	double co = t.coeff;
	if (co < 0.0)
		co *= -1.0;

	if (t.coeff < 0.0)
		fout << "-";

	if (co >= 1.00001 || co <= 0.99999)
		fout << co;
	if (t.a != 0)
	{
		fout << "x";
		if (t.a != 1)
			fout << t.a;
	}
	if (t.b != 0)
	{
		fout << "y";
		if (t.b != 1)
			fout << t.b;
	}
	if (t.c != 0)
	{
		fout << "z";
		if (t.c != 1)
			fout << t.c;
	}
	if (t.d != 0)
	{
		fout << "w";
		if (t.d != 1)
			fout << t.d;
	}
	return fout;
}

term operator-(term t)
{
	t.coeff *= -1.0;
	return t;
}

term operator*(term t1, term t2)
{
	term result;
	result.coeff = t1.coeff * t2.coeff;
	result.a = t1.a + t2.a;
	result.b = t1.b + t2.b;
	result.c = t1.c + t2.c;
	result.d = t1.d + t2.d;
	return result;
}

term operator*(double d, term t)
{
	t.coeff *= d;
	return t;
}

term operator*(term t, double d)
{
	t.coeff *= d;
	return t;
}

term operator/(term t1, term t2)
{
	term result;
	result.coeff = t1.coeff / t2.coeff;
	result.a = t1.a - t2.a;
	result.b = t1.b - t2.b;
	result.c = t1.c - t2.c;
	result.d = t1.d - t2.d;
	return result;
}

term operator/(double d, term t)
{
	t.coeff = d/t.coeff;
	t.a *= -1;
	t.b *= -1;
	t.c *= -1;
	t.d *= -1;
	return t;
}

term operator/(term t, double d)
{
	t.coeff /= d;
	return t;
}

bool operator<(term t1, term t2)
{
	int d1 = t1.degree(), d2 = t2.degree();
	if (d1 > d2)
		return true;
	else if (d1 < d2)
		return false;
	else
		return ((t1.a > t2.a) ||
				(t1.a == t2.a && t1.b > t2.b) ||
				(t1.a == t2.a && t1.b == t2.b && t1.c > t2.c) ||
				(t1.a == t2.a && t1.b == t2.b && t1.c == t2.c && t1.d > t2.d));
}

bool operator>(term t1, term t2)
{
	int d1 = t1.degree(), d2 = t2.degree();
	if (d1 < d2)
		return true;
	else if (d1 > d2)
		return false;
	else
		return ((t1.a < t2.a) ||
				(t1.a == t2.a && t1.b < t2.b) ||
				(t1.a == t2.a && t1.b == t2.b && t1.c < t2.c) ||
				(t1.a == t2.a && t1.b == t2.b && t1.c == t2.c && t1.d < t2.d));
}

bool operator==(term t1, term t2)
{
	return (t1.a == t2.a && t1.b == t2.b && t1.c == t2.c && t1.d == t2.d);
}

}