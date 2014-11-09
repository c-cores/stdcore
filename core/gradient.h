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
struct grad : vec<t, s+1>
{
	grad()
	{

	}

	~grad()
	{

	}

	vec<t, s> normal(vec<t, s> radius, vec<t, s> tangent)
	{
		vec<t, s> a = cross(radius, tangent);
		vec<t, s> b = cross(radius, a);

		vec<t, s> n;
		for (int i = 0; i < s; i++)
			n[i] = (*this)[i];

		a += radius*dot(a, n);
		b += radius*dot(b, n);

		return norm(cross(a, b));
	}
};

// f = -g
// df/dx = -dg/dx
// df/dy = -dg/dy
// df/dz = -dg/dz
template <class t, int s>
grad<t, s> operator-(grad<t, s> v)
{
	grad<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.data[i] = -v.data[i];
	return ret;
}

// f = g + h
// df/dx = dg/dx + dh/dx
// df/dy = dg/dy + dh/dy
// df/dz = dg/dz + dh/dz
template <class t, int s>
grad<t, s> operator+(grad<t, s> v1, grad<t, s> v2)
{
	grad<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.data[i] = v1.data[i] + v2.data[i];
	return ret;
}

// f = g - h
// df/dx = dg/dx - dh/dx
// df/dy = dg/dy - dh/dy
// df/dz = dg/dz - dh/dz
template <class t, int s>
grad<t, s> operator-(grad<t, s> v1, grad<t, s> v2)
{
	grad<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.data[i] = v1.data[i] - v2.data[i];
	return ret;
}

// f = g * h
// df/dx = g * dh/dx + h * dg/dx
// df/dy = g * dh/dy + h * dg/dy
// df/dz = g * dh/dz + h * dg/dz
template <class t, int s>
grad<t, s> operator*(grad<t, s> v1, grad<t, s> v2)
{
	grad<t, s> ret;
	ret.data[s] = v1.data[s] * v2.data[s];
	for (int i = 0; i < s; i++)
		ret.data[i] = v1.data[s]*v2.data[i] + v2.data[s]*v1.data[i];
	return ret;
}

// f = g / h
// df/dx = (h * dg/dx - g * dh/dx)/(h*h)
// df/dy = (h * dg/dy - g * dh/dy)/(h*h)
// df/dz = (h * dg/dz - g * dh/dz)/(h*h)
template <class t, int s>
grad<t, s> operator/(grad<t, s> v1, grad<t, s> v2)
{
	grad<t, s> ret;
	ret.data[s] = v1.data[s] / v2.data[s];
	for (int i = 0; i < s; i++)
		ret.data[i] = (v2.data[s]*v1.data[i] - v1.data[s]*v2.data[i])/(v2.data[s]*v2.data[s]);
	return ret;
}

// f = g + c
// df/dx = dg/dx
// df/dy = dg/dy
// df/dz = dg/dz
template <class t, int s>
grad<t, s> operator+(grad<t, s> v1, t v2)
{
	grad<t, s> ret;
	ret.data[s] = v1.data[s] + v2;
	for (int i = 0; i < s; i++)
		ret.data[i] = v1.data[i];
	return ret;
}

// f = g - c
// df/dx = dg/dx
// df/dy = dg/dy
// df/dz = dg/dz
template <class t, int s>
grad<t, s> operator-(grad<t, s> v1, t v2)
{
	grad<t, s> ret;
	ret.data[s] = v1.data[s] - v2;
	for (int i = 0; i < s; i++)
		ret.data[i] = v1.data[i];
	return ret;
}

// f = g * c
// df/dx = dg/dx * c
// df/dy = dg/dy * c
// df/dz = dg/dz * c
template <class t, int s>
grad<t, s> operator*(grad<t, s> v1, t v2)
{
	grad<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.data[i] = v1.data[i] * v2;
	return ret;
}

// f = g / c
// df/dx = dg/dx / c
// df/dy = dg/dy / c
// df/dz = dg/dz / c
template <class t, int s>
grad<t, s> operator/(grad<t, s> v1, t v2)
{
	grad<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.data[i] = v1.data[i] / v2;
	return ret;
}

// f = c + g
// df/dx = dg/dx
// df/dy = dg/dy
// df/dz = dg/dz
template <class t, int s>
grad<t, s> operator+(t v1, grad<t, s> v2)
{
	grad<t, s> ret;
	ret.data[s] = v1 + v2.data[s];
	for (int i = 0; i < s; i++)
		ret.data[i] = v2.data[i];
	return ret;
}

// f = c - g
// df/dx = -dg/dx
// df/dy = -dg/dy
// df/dz = -dg/dz
template <class t, int s>
grad<t, s> operator-(t v1, grad<t, s> v2)
{
	grad<t, s> ret;
	ret.data[s] = v1 - v2.data[s];
	for (int i = 0; i < s; i++)
		ret.data[i] = -v2.data[i];
	return ret;
}

// f = c * g
// df/dx = c * dg/dx
// df/dy = c * dg/dy
// df/dz = c * dg/dz
template <class t, int s>
grad<t, s> operator*(t v1, grad<t, s> v2)
{
	grad<t, s> ret;
	for (int i = 0; i < s+1; i++)
		ret.data[i] = v1 * v2.data[i];
	return ret;
}

// f = c / g
// df/dx = -c*(dg/dx) / g^2
// df/dy = -c*(dg/dy) / g^2
// df/dz = -c*(dg/dz) / g^2
template <class t, int s>
grad<t, s> operator/(t v1, grad<t, s> v2)
{
	grad<t, s> ret;
	ret.data[s] = v1 / v2.data[s];
	for (int i = 0; i < s; i++)
		ret.data[i] = -v1*v2.data[i]/(v2.data[s]*v2.data[s]);
	return ret;
}

}

#endif
