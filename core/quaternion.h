/*
 * quaternion.h
 *
 *  Created on: Jul 16, 2015
 *      Author: nbingham
 */

#ifndef quaternion_h
#define quaternion_h

namespace core
{

template <class t>
struct quaternion
{
	quaternion()
	{
		this->a = 0;
		this->b = 0;
		this->c = 0;
		this->d = 0;
	}

	quaternion(t a, t b, t c, t d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}

	quaternion(t a, vector<t, 3> b)
	{
		this->a = a;
		this->b = b[0];
		this->c = b[1];
		this->d = b[2];
	}

	~quaternion()
	{

	}

	t a, b, c, d;

	quaternion &operator=(quaternion c)
	{
		a = c.a;
		b = c.b;
		return *this;
	}

	quaternion &operator+=(quaternion c)
	{
		*this = *this + c;
		return *this;
	}

	quaternion &operator-=(quaternion c)
	{
		*this = *this - c;
		return *this;
	}

	quaternion &operator*=(quaternion c)
	{
		*this = *this * c;
		return *this;
	}

	quaternion &operator/=(quaternion c)
	{
		*this = *this / c;
		return *this;
	}

	quaternion &operator+=(t c)
	{
		*this = *this + c;
		return *this;
	}

	quaternion &operator-=(t c)
	{
		*this = *this - c;
		return *this;
	}

	quaternion &operator*=(t c)
	{
		*this = *this * c;
		return *this;
	}

	quaternion &operator/=(t c)
	{
		*this = *this / c;
		return *this;
	}
};

template <class t0, class t1>
quaternion<t0> operator+(quaternion<t0> q0, quaternion<t1> q1)
{
	return quaternion<t0>(q0.a + q1.a,
						  q0.b + q1.b,
						  q0.c + q1.c,
						  q0.d + q1.d);
}

template <class t0, class t1>
quaternion<t0> operator-(quaternion<t0> q0, quaternion<t1> q1)
{
	return quaternion<t0>(q0.a - q1.a,
						  q0.b - q1.b,
						  q0.c - q1.c,
						  q0.d - q1.d);
}

template <class t0, class t1>
quaternion<t0> operator*(quaternion<t0> q0, quaternion<t1> q1)
{
	return quaternion<t0>(q0.a*q1.a - q0.b*q1.b - q0.c*q1.c - q0.d*q1.d,
						  q0.a*q1.b + q0.b*q1.a + q0.c*q1.d - q0.d*q1.c,
						  q0.a*q1.c - q0.b*q1.d + q0.c*q1.a + q0.d*q1.b,
						  q0.a*q1.d + q0.b*q1.c - q0.c*q1.b + q0.d*q1.a);
}

template <class t0, class t1>
quaternion<t0> operator/(quaternion<t0> q0, quaternion<t1> q1)
{
	t0 m = q1.a*q1.a + q1.b*q1.b + q1.c*q1.c + q1.d*q1.d;
	return quaternion<t0>( q0.a*q1.a + q0.b*q1.b + q0.c*q1.c + q0.d*q1.d,
						  -q0.a*q1.b + q0.b*q1.a - q0.c*q1.d + q0.d*q1.c,
						  -q0.a*q1.c + q0.b*q1.d + q0.c*q1.a - q0.d*q1.b,
						  -q0.a*q1.d - q0.b*q1.c + q0.c*q1.b + q0.d*q1.a);
}

template <class t>
quaternion<t> operator+(quaternion<t> q, t c)
{
	return quaternion<t>(q.a + c,
						  q.b,
						  q.c,
						  q.d);
}

template <class t>
quaternion<t> operator-(quaternion<t> q, t c)
{
	return quaternion<t>(q.a - c,
						 q.b,
						 q.c,
						 q.d);
}

template <class t>
quaternion<t> operator*(quaternion<t> q, t c)
{
	return quaternion<t>(q.a*c,
						 q.b*c,
						 q.c*c,
						 q.d*c);
}

template <class t>
quaternion<t> operator/(quaternion<t> q, t c)
{
	return quaternion<t>(q.a/c,
						 q.b/c,
						 q.c/c,
						 q.d/c);
}

template <class t>
quaternion<t> operator+(t c, quaternion<t> q)
{
	return quaternion<t>(c + q.a,
						 q.b,
						 q.c,
						 q.d);
}

template <class t>
quaternion<t> operator-(t c, quaternion<t> q)
{
	return quaternion<t>(c - q.a,
						 -q.b,
						 -q.c,
						 -q.d);
}

template <class t>
quaternion<t> operator*(t c, quaternion<t> q)
{
	return quaternion<t>(c*q.a,
						 c*q.b,
						 c*q.c,
						 c*q.d);
}

template <class t>
quaternion<t> operator/(t c, quaternion<t> q)
{
	t m = q.a*q.a + q.b*q.b + q.c*q.c + q.d*q.d;
	return quaternion<t>(c*q.a/m,
						 -c*q.b/m,
						 -c*q.c/m,
						 -c*q.d/m);
}

template <class t>
quaternion<t> conj(quaternion<t> a)
{
	return quaternion<t>(a.a, -a.b, -a.c, -a.d);
}

template <class t>
t mag(quaternion<t> a)
{
	return sqrt(a.a*a.a + a.b*a.b + a.c*a.c + a.d*a.d);
}

template <class t>
t arg(quaternion<t> a)
{
	return atan2(a.b, a.a);
}

template <class t>
quaternion<t> sqrt(quaternion<t> a)
{
	t N = sqrt(a + mag(a));
	t s2 = 1.41421356237;

	return quaternion<t>(N/s2, a.a/(s2*N), a.b/(s2*N), a.c/(s2*N));
}

template <class t, class t2>
quaternion<t> pow(quaternion<t> a, t2 p)
{
	t phi = arg(a);
	return pow(mag(a), p)*quaternion<t>(cos(p*phi), sin(p*phi));
}

}

#endif
