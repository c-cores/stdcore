/*
 * poly.cpp
 *
 *  Created on: Nov 17, 2013
 *      Author: nbingham
 */

#include "poly.h"

namespace core
{

simple_poly::simple_poly()
{

}

simple_poly::simple_poly(string s)
{
	int i, j;
	for (i = s.find_first_of("+"), j = 0; i != -1; j = i+1, i = s.find_first_of("+", j))
		terms.push_back(term(s.substr(j, i-j)));
	terms.push_back(term(s.substr(j)));
}

simple_poly::~simple_poly()
{

}

void simple_poly::simplify()
{
	sort_quick(terms);

	for (int i = 1; i < terms.size(); )
	{
		if (terms[i].a == terms[i-1].a && terms[i].b == terms[i-1].b &&
			terms[i].c == terms[i-1].c && terms[i].d == terms[i-1].d)
		{
			terms[i-1].coeff += terms[i].coeff;
			terms.pop(i);
		}
		else if (terms[i].coeff < 0.00001 && terms[i].coeff > -0.00001)
			terms.pop(i);
		else
			i++;
	}
}

simple_poly simple_poly::exponentiate(int e)
{
	simple_poly result = simple_poly("1.0x0y0z0w0");

	for (simple_poly i = *this; e > 0; i = i * i, e >>= 1)
		result = (e & 0x1) > 0 ? result * i : result;

	return result;
}

simple_poly &simple_poly::operator=(simple_poly p)
{
	terms = p.terms;
	return *this;
}

simple_poly &simple_poly::operator+=(simple_poly p)
{
	*this = *this + p;
	return *this;
}

simple_poly &simple_poly::operator-=(simple_poly p)
{
	*this = *this - p;
	return *this;
}

simple_poly &simple_poly::operator*=(simple_poly p)
{
	*this = *this * p;
	return *this;
}

simple_poly &simple_poly::operator/=(simple_poly p)
{
	*this = (*this / p).first;
	return *this;
}

simple_poly &simple_poly::operator=(term p)
{
	terms.clear();
	terms.push_back(p);
	return *this;
}

simple_poly &simple_poly::operator+=(term p)
{
	*this = *this + p;
	return *this;
}

simple_poly &simple_poly::operator-=(term p)
{
	*this = *this - p;
	return *this;
}

simple_poly &simple_poly::operator*=(term p)
{
	*this = *this * p;
	return *this;
}

simple_poly &simple_poly::operator/=(term p)
{
	*this = *this / p;
	return *this;
}

simple_poly simple_poly::operator()(simple_poly x, simple_poly y, simple_poly z, simple_poly w)
{
	simple_poly result;
	for (int i = 0; i < terms.size(); i++)
		result += (terms[i].coeff * x.exponentiate(terms[i].a) * y.exponentiate(terms[i].b) *
									z.exponentiate(terms[i].c) * w.exponentiate(terms[i].d));

	return result;
}

simple_poly simple_poly::operator()(vector<simple_poly, 4> f)
{
	simple_poly result;
	for (int i = 0; i < terms.size(); i++)
		result += (terms[i].coeff * f[0].exponentiate(terms[i].a) * f[1].exponentiate(terms[i].b) *
									f[2].exponentiate(terms[i].c) * f[3].exponentiate(terms[i].d));

	return result;
}

file &operator<<(file &fout, simple_poly p)
{
	for (int i = 0; i < p.terms.size(); i++)
	{
		if (i != 0 && p.terms[i].coeff > 0.0)
			fout << "+";
		fout << p.terms[i];
	}
	return fout;
}

simple_poly operator+(simple_poly p1, simple_poly p2)
{
	simple_poly result;
	int i = 0, j = 0;

	result.terms.reserve(p1.terms.size() + p2.terms.size());
	while (i < p1.terms.size() || j < p2.terms.size())
	{
		if (j >= p2.terms.size() || p1.terms[i] < p2.terms[j])
			result.terms.push_back(p1.terms[i++]);
		if (i >= p1.terms.size() || p2.terms[j] < p1.terms[i])
			result.terms.push_back(p2.terms[j++]);
		else
		{
			result.terms.push_back(term(p1.terms[i].coeff + p2.terms[j].coeff, p1.terms[i].a, p1.terms[i].b, p1.terms[i].c, p1.terms[i].d));
			i++;
			j++;
		}
	}

	return result;
}

simple_poly operator+(simple_poly p, term t)
{
	if (p.terms.size() == 0)
	{
		p.terms.push_back(t);
		return p;
	}

	int i = 0;
	for (i = 0; i < p.terms.size() && p.terms[i] < t; i++);

	if (i < p.terms.size() && p.terms[i] == t)
		p.terms[i].coeff += t.coeff;
	else
		p.terms.push(i, t);

	if (p.terms[i].coeff < 0.00001 && p.terms[i].coeff > -0.00001)
		p.terms.pop(i);

	return p;
}

simple_poly operator+(term t, simple_poly p)
{
	if (p.terms.size() == 0)
	{
		p.terms.push_back(t);
		return p;
	}

	int i = 0;
	for (i = 0; i < p.terms.size() && p.terms[i] < t; i++);

	if (i < p.terms.size() && p.terms[i] == t)
		p.terms[i].coeff += t.coeff;
	else
		p.terms.push(i, t);

	if (p.terms[i].coeff < 0.00001 && p.terms[i].coeff > -0.00001)
		p.terms.pop(i);

	return p;
}

simple_poly operator+(double d, simple_poly p)
{
	if (p.terms.back().a == 0 && p.terms.back().b == 0 &&
		p.terms.back().c == 0 && p.terms.back().d == 0)
		p.terms.back().coeff += d;
	else
		p.terms.push_back(term(d, 0, 0, 0, 0));
	return p;
}

simple_poly operator+(simple_poly p, double d)
{
	if (p.terms.back().a == 0 && p.terms.back().b == 0 &&
		p.terms.back().c == 0 && p.terms.back().d == 0)
		p.terms.back().coeff += d;
	else
		p.terms.push_back(term(d, 0, 0, 0, 0));
	return p;
}

simple_poly operator-(simple_poly p1, simple_poly p2)
{
	simple_poly result;
	int i = 0, j = 0;
	term d;

	//result.terms.reserve(p1.terms.size() + p2.terms.size());
	while (i < p1.terms.size() || j < p2.terms.size())
	{
		if (j >= p2.terms.size() ||  (i < p1.terms.size() && p1.terms[i] < p2.terms[j]))
		{
			result.terms.push_back(p1.terms[i]);
			i++;
		}
		else if (i >= p1.terms.size() || (j < p2.terms.size() && p2.terms[j] < p1.terms[i]))
		{
			result.terms.push_back(-p2.terms[j]);
			j++;
		}
		else
		{
			d = term(p1.terms[i].coeff - p2.terms[j].coeff, p1.terms[i].a, p1.terms[i].b, p1.terms[i].c, p1.terms[i].d);
			if (d.coeff >= 0.00001 || d.coeff <= -0.00001)
				result.terms.push_back(d);
			i++;
			j++;
		}
	}

	return result;
}

simple_poly operator-(simple_poly p, term t)
{
	if (p.terms.size() == 0)
	{
		p.terms.push_back(-t);
		return p;
	}

	int i = 0;
	for (i = 0; i < p.terms.size() && p.terms[i] < t; i++);

	if (i < p.terms.size() && p.terms[i] == t)
		p.terms[i].coeff -= t.coeff;
	else
		p.terms.push(i, t);

	if (p.terms[i].coeff < 0.00001 && p.terms[i].coeff > -0.00001)
		p.terms.pop(i);

	return p;
}

simple_poly operator-(term t, simple_poly p)
{
	if (p.terms.size() == 0)
	{
		p.terms.push_back(t);
		return p;
	}

	int i = 0;
	for (i = 0; i < p.terms.size() && p.terms[i] < t; i++)
		p.terms[i].coeff *= -1;

	if (i < p.terms.size() && p.terms[i] == t)
		p.terms[i].coeff = t.coeff - p.terms[i].coeff;
	else
		p.terms.push(i, t);

	if (p.terms[i].coeff < 0.00001 && p.terms[i].coeff > -0.00001)
		p.terms.pop(i);
	else
		i++;

	for (; i < p.terms.size(); i++)
		p.terms[i].coeff *= -1;

	return p;
}

simple_poly operator-(double d, simple_poly p)
{
	for (int i = 0; i < p.terms.size(); i++)
		p.terms[i].coeff *= -1.0;

	if (p.terms.back().a == 0 && p.terms.back().b == 0 &&
		p.terms.back().c == 0 && p.terms.back().d == 0)
		p.terms.back().coeff += d;
	else
		p.terms.push_back(term(d, 0, 0, 0, 0));

	if (p.terms.back().coeff < 0.00001 && p.terms.back().coeff > -0.00001)
		p.terms.pop_back();

	return p;
}

simple_poly operator-(simple_poly p, double d)
{
	if (p.terms.back().a == 0 && p.terms.back().b == 0 &&
		p.terms.back().c == 0 && p.terms.back().d == 0)
		p.terms.back().coeff -= d;
	else
		p.terms.push_back(term(d, 0, 0, 0, 0));

	if (p.terms.back().coeff < 0.00001 && p.terms.back().coeff > -0.00001)
		p.terms.pop_back();

	return p;
}

simple_poly operator*(simple_poly p1, simple_poly p2)
{
	simple_poly result;
	for (int i = 0; i < p1.terms.size(); i++)
		for (int j = 0; j < p2.terms.size(); j++)
			result.terms.push_back(p1.terms[i] * p2.terms[j]);

	result.simplify();
	return result;
}

simple_poly operator*(simple_poly p, term t)
{
	int i = 0;
	for (i = 0; i < p.terms.size(); i++)
		p.terms[i] *= t;

	sort_quick(p.terms);
	return p;
}

simple_poly operator*(term t, simple_poly p)
{
	for (int i = 0; i < p.terms.size(); i++)
		p.terms[i] *= t;

	sort_quick(p.terms);
	return p;
}

simple_poly operator*(double d, simple_poly p)
{
	for (int i = 0; i < p.terms.size(); i++)
		p.terms[i].coeff *= d;
	return p;
}

simple_poly operator*(simple_poly p, double d)
{
	for (int i = 0; i < p.terms.size(); i++)
		p.terms[i].coeff *= d;
	return p;
}

simple_poly operator/(simple_poly p, term t)
{
	for (int i = 0; i < p.terms.size(); i++)
		p.terms[i] /= t;

	sort_quick(p.terms);
	return p;
}

simple_poly operator/(simple_poly p, double d)
{
	for (int i = 0; i < p.terms.size(); i++)
		p.terms[i].coeff /= d;
	return p;
}

pair<simple_poly, simple_poly> operator/(simple_poly p1, simple_poly p2)
{
	simple_poly result;
	int j = 0, k = 0;

	cout << p1 << " / " << p2 << " = " << endl;

	while (p1.terms.size() > 0 && k < (int)p2.terms.size())
	{
		int i = 0;
		term d = p1.terms[i]/p2.terms[k];
		while (d.a < 0 || d.b < 0 || d.c < 0 || d.d < 0)
		{
			i++;
			if (i >= p1.terms.size())
				break;

			d = p1.terms[i]/p2.terms[k];
		}

		if (i >= p1.terms.size() && j == 0)
			k++;
		else if (i >= p1.terms.size())
			return pair<simple_poly, simple_poly>(result, p1);
		else
		{
			cout << d << "\t\t(" << p1 << ") - (" << p2*d << ") = (";
			result += d;
			p1 -= p2*d;
			j++;
			cout << p1 << ")" << endl;
		}
	}

	return pair<simple_poly, simple_poly>(result, p1);
}

simple_poly gcd(simple_poly p1, simple_poly p2)
{
	pair<simple_poly, simple_poly> r;
	int x = 0;
	while (p2.terms.size() > 0 && x++ < 20)
	{
		cout << p1 << "\t\t\t" << p2 << endl;
		r = p1/p2;
		p1 = p2;
		p2 = r.second;
	}

	return p1;
}

poly::poly()
{
}

poly::poly(string s)
{
	int p0 = s.find_first_of("(");
	int p1 = s.find_first_of(")");
	int p2 = s.find_last_of("(");
	int p3 = s.find_last_of(")");
	string n = s.substr(p0+1, p1 - p0 - 1);
	string d = s.substr(p2+1, p3 - p2 - 1);

	numerator = simple_poly(n);
	denominator = simple_poly(d);
}

poly::~poly()
{

}

void poly::simplify()
{
	numerator.simplify();
	denominator.simplify();
}

poly poly::invert()
{
	poly result;
	result.numerator = denominator;
	result.denominator = numerator;
	return result;
}

poly poly::exponentiate(int e)
{
	poly result = poly("(1.0x0y0z0w0)/(1.0x0y0z0w0)");

	for (poly i = *this; e > 0; i = i * i, e >>= 1)
		result = (e & 0x1) > 0 ? result * i : result;

	return result;
}

poly &poly::operator=(poly p)
{
	numerator = p.numerator;
	denominator = p.denominator;
	return *this;
}

poly &poly::operator+=(poly p)
{
	*this = *this + p;
	return *this;
}

poly &poly::operator-=(poly p)
{
	*this = *this - p;
	return *this;
}

poly &poly::operator*=(poly p)
{
	*this = *this * p;
	return *this;
}

poly &poly::operator/=(poly p)
{
	*this = *this / p;
	return *this;
}

poly poly::operator()(poly x, poly y, poly z, poly w)
{
	poly n, d;
	for (int i = 0; i < numerator.terms.size(); i++)
		n = n + (numerator.terms[i].coeff * x.exponentiate(numerator.terms[i].a) * y.exponentiate(numerator.terms[i].b) *
										 z.exponentiate(numerator.terms[i].c) * w.exponentiate(numerator.terms[i].d));

	for (int i = 0; i < denominator.terms.size(); i++)
		d = d + (denominator.terms[i].coeff * x.exponentiate(denominator.terms[i].a) * y.exponentiate(denominator.terms[i].b) *
										   z.exponentiate(denominator.terms[i].c) * w.exponentiate(denominator.terms[i].d));

	return n/d;
}

poly poly::operator()(vector<poly, 4> f)
{
	poly n, d;
	for (int i = 0; i < numerator.terms.size(); i++)
		n = n + (numerator.terms[i].coeff * f[0].exponentiate(numerator.terms[i].a) * f[1].exponentiate(numerator.terms[i].b) *
										 f[2].exponentiate(numerator.terms[i].c) * f[3].exponentiate(numerator.terms[i].d));

	for (int i = 0; i < denominator.terms.size(); i++)
		d = d + (denominator.terms[i].coeff * f[0].exponentiate(denominator.terms[i].a) * f[1].exponentiate(denominator.terms[i].b) *
										   f[2].exponentiate(denominator.terms[i].c) * f[3].exponentiate(denominator.terms[i].d));

	return n/d;
}

file &operator<<(file &fout, poly p)
{
	fout << "(" << p.numerator << ")/(" << p.denominator << ")";
	return fout;
}

poly operator+(poly p1, poly p2)
{
	poly result;
	for (int i = 0; i < p1.numerator.terms.size(); i++)
		for (int j = 0; j < p2.denominator.terms.size(); j++)
			result.numerator.terms.push_back(p1.numerator.terms[i] * p2.denominator.terms[j]);

	for (int i = 0; i < p1.denominator.terms.size(); i++)
		for (int j = 0; j < p2.numerator.terms.size(); j++)
			result.numerator.terms.push_back(p1.denominator.terms[i] * p2.numerator.terms[j]);

	for (int i = 0; i < p1.denominator.terms.size(); i++)
		for (int j = 0; j < p2.denominator.terms.size(); j++)
			result.denominator.terms.push_back(p1.denominator.terms[i] * p2.denominator.terms[j]);

	result.simplify();
	return result;
}

poly operator+(double d, poly p)
{
	p.numerator = p.numerator + d * p.denominator;
	return p;
}

poly operator+(poly p, double d)
{
	p.numerator = p.numerator + d * p.denominator;
	return p;
}

poly operator-(poly p1, poly p2)
{
	poly result;
	for (int i = 0; i < p1.numerator.terms.size(); i++)
		for (int j = 0; j < p2.denominator.terms.size(); j++)
			result.numerator.terms.push_back(p1.numerator.terms[i] * p2.denominator.terms[j]);

	for (int i = 0; i < p1.denominator.terms.size(); i++)
		for (int j = 0; j < p2.numerator.terms.size(); j++)
			result.numerator.terms.push_back(- p1.denominator.terms[i] * p2.numerator.terms[j]);

	for (int i = 0; i < p1.denominator.terms.size(); i++)
		for (int j = 0; j < p2.denominator.terms.size(); j++)
			result.denominator.terms.push_back(p1.denominator.terms[i] * p2.denominator.terms[j]);

	result.simplify();
	return result;
}

poly operator-(double d, poly p)
{
	p.numerator = d * p.denominator - p.numerator;
	p.simplify();
	return p;
}

poly operator-(poly p, double d)
{
	p.numerator = p.numerator - d * p.denominator;
	p.simplify();
	return p;
}

poly operator*(poly p1, poly p2)
{
	poly result;
	for (int i = 0; i < p1.numerator.terms.size(); i++)
		for (int j = 0; j < p2.numerator.terms.size(); j++)
			result.numerator.terms.push_back(p1.numerator.terms[i] * p2.numerator.terms[j]);

	for (int i = 0; i < p1.denominator.terms.size(); i++)
		for (int j = 0; j < p2.denominator.terms.size(); j++)
			result.denominator.terms.push_back(p1.denominator.terms[i] * p2.denominator.terms[j]);

	result.simplify();
	return result;
}

poly operator*(double d, poly p)
{
	for (int i = 0; i < p.numerator.terms.size(); i++)
		p.numerator.terms[i].coeff *= d;
	return p;
}

poly operator*(poly p, double d)
{
	for (int i = 0; i < p.numerator.terms.size(); i++)
		p.numerator.terms[i].coeff *= d;
	return p;
}

poly operator/(poly p1, poly p2)
{
	poly result;
	for (int i = 0; i < p1.numerator.terms.size(); i++)
		for (int j = 0; j < p2.denominator.terms.size(); j++)
			result.numerator.terms.push_back(p1.numerator.terms[i] * p2.denominator.terms[j]);

	for (int i = 0; i < p1.denominator.terms.size(); i++)
		for (int j = 0; j < p2.numerator.terms.size(); j++)
			result.denominator.terms.push_back(p1.denominator.terms[i] * p2.numerator.terms[j]);

	result.simplify();
	return result;
}

poly operator/(double d, poly p)
{
	poly result;
	for (int i = 0; i < p.denominator.terms.size(); i++)
		p.denominator.terms[i].coeff *= d;
	result.numerator = p.denominator;
	result.denominator = p.numerator;
	return result;
}

poly operator/(poly p, double d)
{
	for (int i = 0; i < p.denominator.terms.size(); i++)
		p.denominator.terms[i].coeff *= d;
	return p;
}

}

