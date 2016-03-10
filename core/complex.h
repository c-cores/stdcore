/*
 * complex.h
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on January 15, 2011.
 * Modified by Ned Bingham on June 10, 2012.
 * Copyright 2011 Sol Union. All rights reserved.
 *
 * Blaze Game Engine v0.11 is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * Blaze Game Engine v0.11 is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Blaze Game Engine v0.11.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "math.h"

#ifndef complex_h
#define complex_h

namespace core
{

template <class t>
struct complex
{
	complex()
	{
		a = 0;
		b = 0;
	}
	complex(t x, t y)
	{
		a = x;
		b = y;
	}

	~complex()
	{
	}

	t a;
	t b;

	complex &operator=(complex c)
	{
		a = c.a;
		b = c.b;
		return *this;
	}

	complex &operator+=(complex c)
	{
		*this = *this + c;
		return *this;
	}

	complex &operator-=(complex c)
	{
		*this = *this - c;
		return *this;
	}

	complex &operator*=(complex c)
	{
		*this = *this * c;
		return *this;
	}

	complex &operator/=(complex c)
	{
		*this = *this / c;
		return *this;
	}

	complex &operator+=(t c)
	{
		*this = *this + c;
		return *this;
	}

	complex &operator-=(t c)
	{
		*this = *this - c;
		return *this;
	}

	complex &operator*=(t c)
	{
		*this = *this * c;
		return *this;
	}

	complex &operator/=(t c)
	{
		*this = *this / c;
		return *this;
	}
};

template <class t>
complex<t> operator+(complex<t> a, complex<t> b)
{
	return complex<t>(a.a + b.a, a.b + b.b);
}

template <class t>
complex<t> operator-(complex<t> a, complex<t> b)
{
	return complex<t>(a.a - b.a, a.b - b.b);
}

template <class t>
complex<t> operator*(complex<t> a, complex<t> b)
{
	return complex<t>(a.a*b.a - a.b*b.b, a.b*b.a + a.a*b.b);
}

template <class t>
complex<t> operator/(complex<t> a, complex<t> b)
{
	t m = (b.a*b.a + b.b*b.b);
	return complex<t>((a.a*b.a - a.b*b.b)/m, (a.b*b.a - a.a*b.b)/m);
}

template <class t>
complex<t> operator+(complex<t> a, t b)
{
	return complex<t>(a.a + b, a.b + b);
}

template <class t>
complex<t> operator-(complex<t> a, t b)
{
	return complex<t>(a.a - b, a.b - b);
}

template <class t>
complex<t> operator*(complex<t> a, t b)
{
	return complex<t>(a.a * b, a.b * b);
}

template <class t>
complex<t> operator/(complex<t> a, t b)
{
	return complex<t>(a.a / b, a.b / b);
}

template <class t>
complex<t> operator+(t a, complex<t> b)
{
	return complex<t>(a + b.a, a + b.a);
}

template <class t>
complex<t> operator-(t a, complex<t> b)
{
	return complex<t>(a - b.a, a - b.b);
}

template <class t>
complex<t> operator*(t a, complex<t> b)
{
	return complex<t>(a * b.a, a * b.b);
}

template <class t>
complex<t> operator/(t a, complex<t> b)
{
	return complex<t>(a / b.a, a / b.b);
}

template <class t>
complex<t> conj(complex<t> a)
{
	return complex<t>(a.a, -a.b);
}

template <class t>
t mag(complex<t> a)
{
	return sqrt(a.a*a.a + a.b*a.b);
}

template <class t>
t arg(complex<t> a)
{
	return atan2(a.b, a.a);
}

template <class t>
complex<t> sqrt(complex<t> a)
{
	t magnitude = mag(a);

	return complex<t>(sqrt((a.a + magnitude)/((t)2)), sgn(a.b)*sqrt(-a.a + magnitude)/((t)2));
}

template <class t, class t2>
complex<t> pow(complex<t> a, t2 p)
{
	t phi = arg(a);
	return pow(mag(a), p)*complex<t>(cos(p*phi), sin(p*phi));
}

}

#endif
