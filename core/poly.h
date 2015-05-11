/*
 * poly.h
 *
 *  Created on: Nov 16, 2013
 *      Author: nbingham
 */

#include "term.h"
#include "array.h"
#include "pair.h"
#include "algorithm.h"

#ifndef poly_h
#define poly_h

namespace core
{

struct simple_poly
{
	simple_poly();
	simple_poly(string s);
	~simple_poly();

	array<term> terms;

	void simplify();
	simple_poly exponentiate(int e);

	simple_poly &operator=(simple_poly p);
	simple_poly &operator+=(simple_poly p);
	simple_poly &operator-=(simple_poly p);
	simple_poly &operator*=(simple_poly p);
	simple_poly &operator/=(simple_poly p);

	simple_poly &operator=(term p);
	simple_poly &operator+=(term p);
	simple_poly &operator-=(term p);
	simple_poly &operator*=(term p);
	simple_poly &operator/=(term p);

	template <class type>
	type operator()(type x, type y, type z, type w)
	{
		type result = 0;
		for (size_t i = 0; i < terms.size(); i++)
			result += terms[i](x, y, z, w);
		return result;
	}

	simple_poly operator()(simple_poly x, simple_poly y, simple_poly z, simple_poly w);

	template <class type>
	type operator()(vector<type, 4> f)
	{
		type result = 0;
		for (size_t i = 0; i < terms.size(); i++)
			result += terms[i](f);
		return result;
	}

	simple_poly operator()(vector<simple_poly, 4> f);
};

file &operator<<(file &fout, simple_poly p);

simple_poly operator+(simple_poly p1, simple_poly p2);
simple_poly operator+(simple_poly p, term t);
simple_poly operator+(term t, simple_poly p);
simple_poly operator+(double d, simple_poly p);
simple_poly operator+(simple_poly p, double d);

simple_poly operator-(simple_poly p1, simple_poly p2);
simple_poly operator-(simple_poly p, term t);
simple_poly operator-(term t, simple_poly p);
simple_poly operator-(double d, simple_poly p);
simple_poly operator-(simple_poly p, double d);

simple_poly operator*(simple_poly p1, simple_poly p2);
simple_poly operator*(simple_poly p, term t);
simple_poly operator*(term t, simple_poly p);
simple_poly operator*(double d, simple_poly p);
simple_poly operator*(simple_poly p, double d);

simple_poly operator/(simple_poly p, term t);
simple_poly operator/(simple_poly p, double d);
pair<simple_poly, simple_poly> operator/(simple_poly p1, simple_poly p2);

simple_poly gcd(simple_poly p1, simple_poly p2);

struct poly
{
	poly();
	poly(string s);
	~poly();

	simple_poly numerator;
	simple_poly denominator;

	void simplify();
	poly invert();
	poly exponentiate(int e);

	poly &operator=(poly p);
	poly &operator+=(poly p);
	poly &operator-=(poly p);
	poly &operator*=(poly p);
	poly &operator/=(poly p);

	template <class type>
	type operator()(type x, type y, type z, type w)
	{
		type n = 0, d = 0;
		for (size_t i = 0; i < numerator.terms.size(); i++)
				n += numerator.terms[i](x, y, z, w);
		for (size_t i = 0; i < denominator.terms.size(); i++)
				d += denominator.terms[i](x, y, z, w);

		return n/d;
	}

	poly operator()(poly x, poly y, poly z, poly w);

	template <class type>
	type operator()(vector<type, 4> f)
	{
		type n = 0, d = 0;
		for (size_t i = 0; i < numerator.terms.size(); i++)
				n += numerator.terms[i](f);
		for (size_t i = 0; i < denominator.terms.size(); i++)
				d += denominator.terms[i](f);

		return n/d;
	}

	poly operator()(vector<poly, 4> f);
};

file &operator<<(file &fout, poly p);

poly operator+(poly p1, poly p2);
poly operator+(double d, poly p);
poly operator+(poly p, double d);

poly operator-(poly p1, poly p2);
poly operator-(double d, poly p);
poly operator-(poly p, double d);

poly operator*(poly p1, poly p2);
poly operator*(double d, poly p);
poly operator*(poly p, double d);

poly operator/(poly p1, poly p2);
poly operator/(double d, poly p);
poly operator/(poly p, double d);

}

#endif
