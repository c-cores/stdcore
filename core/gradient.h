/*
 * gradient.h
 *
 *  Created on: Feb 12, 2014
 *      Author: nbingham
 */

#include "vector.h"

#ifndef gradient_h
#define gradient_h

namespace core
{

template <class t, int s>
struct gradient
{
	gradient()
	{
		for (int i = 0; i < s+1; i++)
			elems[i] = 0;
	}

	gradient(t c)
	{
		elems[s] = c;
		for (int i = 0; i < s; i++)
			elems[i] = 0;
	}

	~gradient()
	{

	}

	t elems[s+1];

	vector<t, s> normal()
	{
		vector<t, s> result;
		for (int i = 0; i < s; i++)
			result.elems[i] = elems[i];
		return norm(result);
	}

	template <class t1>
	gradient<t, s> &operator=(gradient<t1, s> g)
	{
		for (int i = 0; i < s+1; i++)
			elems[i] = g.elems[i];
		return *this;
	}

	gradient<t, s> &operator=(t c)
	{
		elems[s] = c;
		for (int i = 0; i < s; i++)
			elems[i] = 0;
		return *this;
	}

	template <class t1>
	gradient<t, s> &operator+=(gradient<t1, s> g)
	{
		*this = *this + g;
		return *this;
	}

	template <class t1>
	gradient<t, s> &operator-=(gradient<t1, s> g)
	{
		*this = *this - g;
		return *this;
	}

	template <class t1>
	gradient<t, s> &operator*=(gradient<t1, s> g)
	{
		*this = *this * g;
		return *this;
	}

	template <class t1>
	gradient<t, s> &operator/=(gradient<t1, s> g)
	{
		*this = *this / g;
		return *this;
	}

	gradient<t, s> &operator+=(t g)
	{
		*this = *this + g;
		return *this;
	}

	gradient<t, s> &operator-=(t g)
	{
		*this = *this - g;
		return *this;
	}

	gradient<t, s> &operator*=(t g)
	{
		*this = *this * g;
		return *this;
	}

	gradient<t, s> &operator/=(t g)
	{
		*this = *this / g;
		return *this;
	}

	t &operator[](int i)
	{
		return elems[i];
	}

	t operator[](int i) const
	{
		return elems[i];
	}
};

template <class t, int s>
file &operator<<(file &os, gradient<t, s> g)
{
	os << "(" << g.elems[s] << ": ";
	for (int i = 0; i < s; i++)
	{
		if (i != 0)
			os << ", ";
		os << g.elems[i];
	}
	os << ")";
	return os;
}

// f = -g
// df/dx = -dg/dx
// df/dy = -dg/dy
// df/dz = -dg/dz
template <class t, int s>
gradient<t, s> operator-(gradient<t, s> v)
{
	gradient<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.elems[i] = -v.elems[i];
	return ret;
}

// f = g + h
// df/dx = dg/dx + dh/dx
// df/dy = dg/dy + dh/dy
// df/dz = dg/dz + dh/dz
template <class t0, class t1, int s>
gradient<t0, s> operator+(gradient<t0, s> v1, gradient<t1, s> v2)
{
	gradient<t0, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.elems[i] = v1.elems[i] + v2.elems[i];
	return ret;
}

// f = g - h
// df/dx = dg/dx - dh/dx
// df/dy = dg/dy - dh/dy
// df/dz = dg/dz - dh/dz
template <class t0, class t1, int s>
gradient<t0, s> operator-(gradient<t0, s> v1, gradient<t1, s> v2)
{
	gradient<t0, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.elems[i] = v1.elems[i] - v2.elems[i];
	return ret;
}

// f = g * h
// df/dx = g * dh/dx + h * dg/dx
// df/dy = g * dh/dy + h * dg/dy
// df/dz = g * dh/dz + h * dg/dz
template <class t0, class t1, int s>
gradient<t0, s> operator*(gradient<t0, s> v1, gradient<t1, s> v2)
{
	gradient<t0, s> ret;
	ret.elems[s] = v1.elems[s] * v2.elems[s];
	for (int i = 0; i < s; i++)
		ret.elems[i] = v1.elems[s]*v2.elems[i] + v2.elems[s]*v1.elems[i];
	return ret;
}

// f = g / h
// df/dx = (h * dg/dx - g * dh/dx)/(h*h)
// df/dy = (h * dg/dy - g * dh/dy)/(h*h)
// df/dz = (h * dg/dz - g * dh/dz)/(h*h)
template <class t0, class t1, int s>
gradient<t0, s> operator/(gradient<t0, s> v1, gradient<t1, s> v2)
{
	gradient<t0, s> ret;
	ret.elems[s] = v1.elems[s] / v2.elems[s];
	for (int i = 0; i < s; i++)
		ret.elems[i] = (v2.elems[s]*v1.elems[i] - v1.elems[s]*v2.elems[i])/(v2.elems[s]*v2.elems[s]);
	return ret;
}

// f = g + c
// df/dx = dg/dx
// df/dy = dg/dy
// df/dz = dg/dz
template <class t, int s>
gradient<t, s> operator+(gradient<t, s> v1, t v2)
{
	v1.elems[s] += v2;
	return v1;
}

// f = g - c
// df/dx = dg/dx
// df/dy = dg/dy
// df/dz = dg/dz
template <class t, int s>
gradient<t, s> operator-(gradient<t, s> v1, t v2)
{
	v1.elems[s] -= v2;
	return v1;
}

// f = g * c
// df/dx = dg/dx * c
// df/dy = dg/dy * c
// df/dz = dg/dz * c
template <class t, int s>
gradient<t, s> operator*(gradient<t, s> v1, t v2)
{
	gradient<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.elems[i] = v1.elems[i] * v2;
	return ret;
}

// f = g / c
// df/dx = dg/dx / c
// df/dy = dg/dy / c
// df/dz = dg/dz / c
template <class t, int s>
gradient<t, s> operator/(gradient<t, s> v1, t v2)
{
	gradient<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.elems[i] = v1.elems[i] / v2;
	return ret;
}

// f = c + g
// df/dx = dg/dx
// df/dy = dg/dy
// df/dz = dg/dz
template <class t, int s>
gradient<t, s> operator+(t v1, gradient<t, s> v2)
{
	gradient<t, s> ret;
	ret.elems[s] = v1 + v2.elems[s];
	for (int i = 0; i < s; i++)
		ret.elems[i] = v2.elems[i];
	return ret;
}

// f = c - g
// df/dx = -dg/dx
// df/dy = -dg/dy
// df/dz = -dg/dz
template <class t, int s>
gradient<t, s> operator-(t v1, gradient<t, s> v2)
{
	gradient<t, s> ret;
	ret.elems[s] = v1 - v2.elems[s];
	for (int i = 0; i < s; i++)
		ret.elems[i] = -v2.elems[i];
	return ret;
}

// f = c * g
// df/dx = c * dg/dx
// df/dy = c * dg/dy
// df/dz = c * dg/dz
template <class t, int s>
gradient<t, s> operator*(t v1, gradient<t, s> v2)
{
	gradient<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.elems[i] = v1 * v2.elems[i];
	return ret;
}

// f = c / g
// df/dx = -c*(dg/dx) / g^2
// df/dy = -c*(dg/dy) / g^2
// df/dz = -c*(dg/dz) / g^2
template <class t, int s>
gradient<t, s> operator/(t v1, gradient<t, s> v2)
{
	gradient<t, s> ret;
	ret.elems[s] = v1 / v2.elems[s];
	for (int i = 0; i < s; i++)
		ret.elems[i] = -v1*v2.elems[i]/(v2.elems[s]*v2.elems[s]);
	return ret;
}

// f = sqrt(g)
// df/dx = 0.5*(dg/dx)/sqrt(g)
// df/dy = 0.5*(dg/dx)/sqrt(g)
// df/dz = 0.5*(dg/dx)/sqrt(g)
template <class t, int s>
gradient<t, s> sqrt(gradient<t, s> g)
{
	gradient<t, s> ret;
	t sqrtg = ::sqrt(g.elems[s]);
	ret.elems[s] = sqrtg;
	for (int i = 0; i < s; i++)
		ret.elems[i] = g.elems[i]/((t)2*sqrtg);
	return ret;
}

// f = b^e
// df/dx = e*b^(e-1)*(db/dx)
// df/dy = e*b^(e-1)*(db/dy)
// df/dz = e*b^(e-1)*(db/dz)
template <class t, int s>
gradient<t, s> pow(gradient<t, s> b, t e)
{
	gradient<t, s> ret;
	t dg = ::pow(b.elems[s], e-(t)1);
	ret.elems[s] = dg*b.elems[s];
	for (int i = 0; i < s; i++)
		ret.elems[i] = e*dg*b.elems[i];
	return ret;
}

// f = b^e
// df/dx = b^e*(de/dx)*ln(b)
// df/dy = b^e*(de/dy)*ln(b)
// df/dz = b^e*(de/dz)*ln(b)
template <class t, int s>
gradient<t, s> pow(t b, gradient<t, s> e)
{
	gradient<t, s> ret;
	ret.elems[s] = ::pow(b, e.elems[s]);
	t lnb = log(b);
	for (int i = 0; i < s; i++)
		ret.elems[i] = ret.elems[s]*lnb*e.elems[i];
	return ret;
}

// f = b^e
// df/dx = b^e*((db/dx)*e/b + (de/dx)*ln(b))
// df/dy = b^e*((db/dy)*e/b + (de/dy)*ln(b))
// df/dz = b^e*((db/dz)*e/b + (de/dz)*ln(b))
template <class t0, class t1, int s>
gradient<t0, s> pow(gradient<t0, s> b, gradient<t1, s> e)
{
	gradient<t0, s> ret;
	ret.elems[s] = ::pow(b.elems[s], e.elems[s]);
	t0 e_b = e.elems[s]/b.elems[s];
	t0 lnb = log(b.elems[s]);
	for (int i = 0; i < s; i++)
		ret.elems[i] = ret.elems[s]*(b.elems[i]*e_b + e.elems[i]*lnb);
	return ret;
}

// f = log_b(x)
// df/dx = (dx/dx)/(x*ln(b))
// df/dy = (dx/dy)/(x*ln(b))
// df/dz = (dx/dz)/(x*ln(b))
template <class t, int s>
gradient<t, s> log(t b, gradient<t, s> x)
{
	gradient<t, s> ret;
	ret.elems[s] = log(x.elems[s])/log(b);
	t lnb = log(b.elems[s]);
	for (int i = 0; i < s; i++)
		ret.elems[i] = x.elems[i]/(x.elems[s]*lnb);
	return ret;
}

// f = sin(g)
// df/dx = cos(g)*(dg/dx)
// df/dy = cos(g)*(dg/dy)
// df/dz = cos(g)*(dg/dz)
template <class t, int s>
gradient<t, s> sin(gradient<t, s> g)
{
	gradient<t, s> ret;
	t sg = sin(g.elems[s]);
	t cg = cos(g.elems[s]);
	ret.elems[s] = sg;
	for (int i = 0; i < s; i++)
		ret.elems[i] = cg*g.elems[i];
	return ret;
}

// f = cos(g)
// df/dx = -sin(g)*(dg/dx)
// df/dy = -sin(g)*(dg/dy)
// df/dz = -sin(g)*(dg/dz)
template <class t, int s>
gradient<t, s> cos(gradient<t, s> g)
{
	gradient<t, s> ret;
	t sg = sin(g.elems[s]);
	t cg = cos(g.elems[s]);
	ret.elems[s] = cg;
	for (int i = 0; i < s; i++)
		ret.elems[i] = -sg*g.elems[i];
	return ret;
}

// f = tan(g)
// df/dx = sec2(g)*(dg/dx)
// df/dy = sec2(g)*(dg/dy)
// df/dz = sec2(g)*(dg/dz)
template <class t, int s>
gradient<t, s> tan(gradient<t, s> g)
{
	gradient<t, s> ret;
	t sg = sin(g.elems[s]);
	t cg = cos(g.elems[s]);
	ret.elems[s] = sg/cg;
	for (int i = 0; i < s; i++)
		ret.elems[i] = g.elems[i]/(cg*cg);
	return ret;
}

// f = cot(g)
// df/dx = -csc2(g)*(dg/dx)
// df/dy = -csc2(g)*(dg/dy)
// df/dz = -csc2(g)*(dg/dz)
template <class t, int s>
gradient<t, s> cot(gradient<t, s> g)
{
	gradient<t, s> ret;
	t sg = sin(g.elems[s]);
	t cg = cos(g.elems[s]);
	ret.elems[s] = cg/sg;
	for (int i = 0; i < s; i++)
		ret.elems[i] = -g.elems[i]/(sg*sg);
	return ret;
}

template <class t, int s>
gradient<t, s> abs(gradient<t, s> g)
{
	return g.elems[s] < (t)0 ? -g : g;
}

template <class t, int s>
gradient<t, s> floor(gradient<t, s> g)
{
	g.elems[s] = ::floor(g.elems[s]);
	for (int i = 0; i < s; i++)
		g.elems[i] = (t)0;
	return g;
}

template <class t, int s>
gradient<t, s> ceil(gradient<t, s> g)
{
	g.elems[s] = ceil(g.elems[s]);
	for (int i = 0; i < s; i++)
		g.elems[i] = (t)0;
	return g;
}

template <class t, int s>
bool operator<(gradient<t, s> l, t r)
{
	return l.elems[s] < r;
}

template <class t, int s>
bool operator<=(gradient<t, s> l, t r)
{
	return l.elems[s] <= r;
}

template <class t, int s>
bool operator>(gradient<t, s> l, t r)
{
	return l.elems[s] > r;
}

template <class t, int s>
bool operator>=(gradient<t, s> l, t r)
{
	return l.elems[s] >= r;
}

template <class t, int s>
bool operator==(gradient<t, s> l, t r)
{
	return l.elems[s] == r;
}

template <class t, int s>
bool operator!=(gradient<t, s> l, t r)
{
	return l.elems[s] != r;
}

template <class t, int s>
bool operator<(t l, gradient<t, s> r)
{
	return l < r.elems[s];
}

template <class t, int s>
bool operator<=(t l, gradient<t, s> r)
{
	return l <= r.elems[s];
}

template <class t, int s>
bool operator>(t l, gradient<t, s> r)
{
	return l > r.elems[s];
}

template <class t, int s>
bool operator>=(t l, gradient<t, s> r)
{
	return l >= r.elems[s];
}

template <class t, int s>
bool operator==(t l, gradient<t, s> r)
{
	return l == r.elems[s];
}

template <class t, int s>
bool operator!=(t l, gradient<t, s> r)
{
	return l != r.elems[s];
}

template <class t, int s>
bool operator<(gradient<t, s> l, gradient<t, s> r)
{
	return l.elems[s] < r.elems[s];
}

template <class t, int s>
bool operator<=(gradient<t, s> l, gradient<t, s> r)
{
	return l.elems[s] <= r.elems[s];
}

template <class t, int s>
bool operator>(gradient<t, s> l, gradient<t, s> r)
{
	return l.elems[s] > r.elems[s];
}

template <class t, int s>
bool operator>=(gradient<t, s> l, gradient<t, s> r)
{
	return l.elems[s] >= r.elems[s];
}

template <class t, int s>
bool operator==(gradient<t, s> l, gradient<t, s> r)
{
	return l.elems[s] == r.elems[s];
}

template <class t, int s>
bool operator!=(gradient<t, s> l, gradient<t, s> r)
{
	return l.elems[s] != r.elems[s];
}

}

#endif
