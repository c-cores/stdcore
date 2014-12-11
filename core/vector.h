/*
 * vector.h
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on December 7, 2011.
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
#include "ref.h"
#include "file.h"
#include <stdarg.h>

#ifndef vector_h
#define vector_h

namespace core
{

template <class t, int s>
struct vec
{
	vec()
	{
	}

	vec(const t v[s])
	{
		int i;

		for (i = 0; i < s; i++)
			this->data[i] = v[i];
	}

	template <class t2, int s2>
	vec(vec<t2, s2> v)
	{
		for (int i = 0; i < min(s, s2); i++)
			this->data[i] = (t)v.data[i];
	}

	vec(const char *str)
	{
		char num[32];
		int j = 0, k = 0;
		for (int i = 0; str[i] != '\0' && k < s; i++)
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.' || str[i] == '-' || str[i] == 'e' || str[i] == 'E')
				num[j++] = str[i];
			else if (j > 0)
			{
				num[j++] = '\0';
				this->data[k++] = string(num).to_double();
				j = 0;
			}
		}

		if (j > 0)
		{
			num[j++] = '\0';
			this->data[k++] = string(num).to_double();
			j = 0;
		}

		for (; k < s; k++)
			this->data[k] = 0.0;
	}

	template <class t2>
	vec(t2 first, ...)
	{
		va_list arguments;
		int i;

		va_start(arguments, first);
		this->data[0] = first;
		for (i = 1; i < s; i++)
			this->data[i] = (t)va_arg(arguments, t2);
		va_end(arguments);
	}

	vec(float first, ...)
	{
		va_list arguments;
		int i;

		va_start(arguments, first);
		this->data[0] = first;
		for (i = 1; i < s; i++)
			this->data[i] = (t)va_arg(arguments, double);
		va_end(arguments);
	}

	~vec()
	{
	}

	t data[s];

	template <class t2, int s2>
	vec<t, s> &operator=(vec<t2, s2> v)
	{
		int i;
		for (i = 0; i < min(s, s2); i++)
			this->data[i] = (t)v.data[i];
		return *this;
	}

	template <class t2, int s2>
	vec<t, s> &operator=(const t2 v[s2])
	{
		int i;
		for (i = 0; i < min(s, s2); i++)
			this->data[i] = v[i];
		return *this;
	}

	template <class t2>
	vec<t, s> &operator+=(vec<t2, s> v)
	{
		*this = *this + v;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator-=(vec<t2, s> v)
	{
		*this = *this - v;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator*=(vec<t2, s> v)
	{
		*this = *this * v;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator/=(vec<t2, s> v)
	{
		*this = *this / v;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator+=(t2 f)
	{
		*this = *this + f;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator-=(t2 f)
	{
		*this = *this - f;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator*=(t2 f)
	{
		*this = *this * f;
		return *this;
	}

	template <class t2>
	vec<t, s> &operator/=(t2 f)
	{
		*this = *this / f;
		return *this;
	}

	template <int s2>
	operator vec<t, s2>()
	{
		vec<t, s2> ret;
		for (int i = 0; i < min(s, s2); i++)
			ret[i] = data[i];
		return ret;
	}

	vec<ref<t>, s> operator()(const char *str)
	{
		int indices[2];

		char num[32];
		int j = 0, k = 0;
		for (int i = 0; str[i] != '\0' && k < 2; i++)
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
				num[j++] = str[i];
			else if (j > 0)
			{
				num[j++] = '\0';
				indices[k++] = string(num).to_long();
				j = 0;
			}
		}

		if (j > 0 && k < 2)
		{
			num[j++] = '\0';
			indices[k++] = string(num).to_long();
			j = 0;
		}

		if (k < 2)
			indices[1] = indices[0];

		vec<ref<t>, s> result;
		for (int i = indices[0]; i < min(s, indices[1]); i++)
			result.data[i-indices[0]] = ref<t>(this->data[i]);

		return result;
	}

	vec<ref<t>,s> operator()(int start, int end)
	{
		vec<ref<t>, s> result;
		for (int i = start; i < min(s, end); i++)
			result.data[i-start] = ref<t>(data[i]);
		return result;
	}

	t &operator()(int index)
	{
		return data[index];
	}

	t &operator[](int index)
	{
		return data[index];
	}

	vec<t, s> &swap(int a, int b)
	{
		t temp = data[a];
		data[a] = data[b];
		data[b] = temp;
		return *this;
	}

	template <class t2>
	void set(t2 v)
	{
		int i;

		for (i = 0; i < s; i++)
			this->data[i] = (t)v;
	}
};

template <class t, int s>
file &operator<<(file &f, vec<t, s> v)
{
	f << "[";
	for (int i = 0; i < s; i++)
	{
		if (i != 0)
			f << " ";
		f << v[i];
	}
	f << "]";
	return f;
}

/* negation
 *
 * negates each of v components and returns
 * the resulting vector.
 */
template <class t, int s>
vec<t, s> operator-(vec<t, s> v)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = -v.data[i];

	return result;
}

/* vector division
 *
 * Returns the resulting vector generated by taking each of
 * v1's components and adding it to the corresponding component
 * of v2.
 */
template <class t1, class t2, int s1, int s2>
vec<t1, s1> operator+(vec<t1, s1> v1, vec<t2, s2> v2)
{
	vec<t1, s1> result;
	int i;

	for (i = 0; i < (s1 < s2 ? s1 : s2); i++)
		result.data[i] = v1.data[i] + v2.data[i];

	return result;
}

/* vector division
 *
 * Returns the resulting vector generated by taking each of
 * v2's components and subtracting it from the corresponding component
 * of v1.
 */
template <class t1, class t2, int s1, int s2>
vec<t1, s1> operator-(vec<t1, s1> v1, vec<t2, s2> v2)
{
	vec<t1, s1> result;
	int i;

	for (i = 0; i < (s1 < s2 ? s1 : s2); i++)
		result.data[i] = v1.data[i] - v2.data[i];

	return result;
}

/* vector division
 *
 * Returns the resulting vector generated by taking each of
 * v1's components and multiplying it by the corresponding component
 * of v2.
 */
template <class t1, class t2, int s1, int s2>
vec<t1, s1> operator*(vec<t1, s1> v1, vec<t2, s2> v2)
{
	vec<t1, s1> result;
	int i;

	for (i = 0; i < (s1 < s2 ? s1 : s2); i++)
		result.data[i] = v1.data[i] * v2.data[i];

	return result;
}

/* vector division
 *
 * Returns the resulting vector generated by taking each of
 * v1's components and dividing it by the corresponding component
 * of v2.
 */
template <class t1, class t2, int s1, int s2>
vec<t1, s1> operator/(vec<t1, s1> v1, vec<t2, s2> v2)
{
	vec<t1, s1> result;
	int i;

	for (i = 0; i < (s1 < s2 ? s1 : s2); i++)
		result.data[i] = v1.data[i] / v2.data[i];

	return result;
}

/* scalar-vector addition
 *
 * This creates a vector who's components are f plus by the
 * corresponding component in the vector v.
 */
template <class t, class t2, int s>
vec<t, s> operator+(t2 f, vec<t, s> v)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = f + v.data[i];

	return result;
}

/* scalar-vector subtraction
 *
 * This creates a vector who's components are f minus by the
 * corresponding component in the vector v.
 */
template <class t, class t2, int s>
vec<t, s> operator-(t2 f, vec<t, s> v)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = f - v.data[i];

	return result;
}

/* scalar-vector multiplication
 *
 * This creates a vector who's components are f multiplied by
 * the corresponding component in the vector v.
 */
template <class t, class t2, int s>
vec<t, s> operator*(t2 f, vec<t, s> v)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = f * v.data[i];

	return result;
}

/* scalar-vector division
 *
 * This creates a vector who's components are f divided by the
 * corresponding component in the vector v.
 */
template <class t, class t2, int s>
vec<t, s> operator/(t2 f, vec<t, s> v)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = f / v.data[i];

	return result;
}

/* vector-scalar addition
 *
 * Adds f to all of the components of v.
 */
template <class t, class t2, int s>
vec<t, s> operator+(vec<t, s> v, t2 f)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = v.data[i] + f;

	return result;
}

/* vector-scalar subtraction
 *
 * Subtracts f from all of the components of v.
 */
template <class t, class t2, int s>
vec<t, s> operator-(vec<t, s> v, t2 f)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = v.data[i] - f;

	return result;
}

// vector-scalar multiplication
template <class t, class t2, int s>
vec<t, s> operator*(vec<t, s> v, t2 f)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = v.data[i] * f;

	return result;
}

// vector-scalar division
template <class t, class t2, int s>
vec<t, s> operator/(vec<t, s> v, t2 f)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = v.data[i] / f;

	return result;
}

// vector-vector comparison
template <class t, class t2, int s>
bool operator==(vec<t, s> v, vec<t2, s> v2)
{
	bool result = true;

	for (int i = 0; i < s; i++)
		result = result && v[i] == v2[i];

	return result;
}

// vector-vector comparison
template <class t, class t2, int s>
bool operator!=(vec<t, s> v, vec<t2, s> v2)
{
	bool result = true;

	for (int i = 0; i < s; i++)
		result = result && v[i] != v2[i];

	return result;
}

// vector-vector comparison
template <class t, class t2, int s>
bool operator<(vec<t, s> v, vec<t2, s> v2)
{
	bool result = true;

	for (int i = 0; i < s; i++)
		result = result && v[i] < v2[i];

	return result;
}

// vector-vector comparison
template <class t, class t2, int s>
bool operator>(vec<t, s> v, vec<t2, s> v2)
{
	bool result = true;

	for (int i = 0; i < s; i++)
		result = result && v[i] > v2[i];

	return result;
}

// vector-vector comparison
template <class t, class t2, int s>
bool operator<=(vec<t, s> v, vec<t2, s> v2)
{
	bool result = true;

	for (int i = 0; i < s; i++)
		result = result && v[i] <= v2[i];

	return result;
}

// vector-vector comparison
template <class t, class t2, int s>
bool operator>=(vec<t, s> v, vec<t2, s> v2)
{
	bool result = true;

	for (int i = 0; i < s; i++)
		result = result && v[i] >= v2[i];

	return result;
}

/* abs
 * (absolute value)
 *
 * This function takes the absolute value of each component in
 * a vector and returns the result.
 */
template <class t, int s>
vec<t, s> abs(vec<t, s> v)
{
	vec<t, s> result;
	int i;

	for (i = 0; i < s; i++)
		result.data[i] = abs(v.data[i]);

	return result;
}

/* norm
 * (normalize)
 *
 * This function returns the normal of a vector
 * n = v/|v|
 */
template <class t, int s>
vec<t, s> norm(vec<t, s> v)
{
	return v/mag(v);
}

/* cross
 * (cross product)
 *
 * Generates the three dimensional cross product of two vectors and returns
 * the resultant vector. (x, y, z)
 */
template <class t1, class t2>
vec<t1, 3> cross(vec<t1, 3> v1, vec<t2, 3> v2)
{
	vec<t1, 3> result;

	result.data[0] = v1.data[1]*v2.data[2] - v1.data[2]*v2.data[1];
	result.data[1] = v1.data[2]*v2.data[0] - v1.data[0]*v2.data[2];
	result.data[2] = v1.data[0]*v2.data[1] - v1.data[1]*v2.data[0];

	return result;
}

/* cross
 * (cross product)
 *
 * Generates the three dimensional cross product of two vectors and returns
 * the resultant vector in homogeneous coordinates. (x, y, z, 1.0)
 */
template <class t1, class t2>
vec<t1, 4> cross(vec<t1, 4> v1, vec<t2, 4> v2)
{
	vec<t1, 4> result;

	result.data[0] = v1.data[1]*v2.data[2] - v1.data[2]*v2.data[1];
	result.data[1] = v1.data[2]*v2.data[0] - v1.data[0]*v2.data[2];
	result.data[2] = v1.data[0]*v2.data[1] - v1.data[1]*v2.data[0];
	result.data[3] = (t1)1;

	return result;
}

/* cross
 * (cross product)
 *
 * Generates the four dimensional cross product of three vectors and returns
 * the resultant vector. (x, y, z, w)
 */
template <class t1, class t2, class t3>
vec<t1, 4> cross(vec<t1, 4> v1, vec<t2, 4> v2, vec<t3, 4> v3)
{
	vec<t1, 4> result;

	result.data[0] =  v1.data[1]*(v2.data[2]*v3.data[3] - v3.data[2]*v2.data[3]) - v1.data[2]*(v2.data[1]*v3.data[3] - v3.data[1]*v2.data[3]) + v1.data[3]*(v2.data[1]*v3.data[2] - v3.data[1]*v2.data[2]);
	result.data[1] = -v1.data[0]*(v2.data[2]*v3.data[3] - v3.data[2]*v2.data[3]) + v1.data[2]*(v2.data[0]*v3.data[3] - v3.data[0]*v2.data[3]) - v1.data[3]*(v2.data[0]*v3.data[2] - v3.data[0]*v2.data[2]);
	result.data[2] =  v1.data[0]*(v2.data[1]*v3.data[3] - v3.data[1]*v2.data[3]) - v1.data[1]*(v2.data[0]*v3.data[3] - v3.data[0]*v2.data[3]) + v1.data[3]*(v2.data[0]*v3.data[1] - v3.data[0]*v2.data[1]);
	result.data[3] = -v1.data[0]*(v2.data[1]*v3.data[2] - v3.data[1]*v2.data[2]) + v1.data[1]*(v2.data[0]*v3.data[2] - v3.data[0]*v2.data[2]) - v1.data[2]*(v2.data[0]*v3.data[1] - v3.data[0]*v2.data[1]);

	return result;
}

/* cross
 * (cross product)
 *
 * Generates the four dimensional cross product of three vectors and returns
 * the result in homogeneous coordinates. (x, y, z, w, 1.0)
 */
template <class t1, class t2, class t3>
vec<t1, 5> cross(vec<t1, 5> v1, vec<t2, 5> v2, vec<t3, 5> v3)
{
	vec<t1, 5> result;

	result.data[0] =  v1.data[1]*(v2.data[2]*v3.data[3] - v3.data[2]*v2.data[3]) - v1.data[2]*(v2.data[1]*v3.data[3] - v3.data[1]*v2.data[3]) + v1.data[3]*(v2.data[1]*v3.data[2] - v3.data[1]*v2.data[2]);
	result.data[1] = -v1.data[0]*(v2.data[2]*v3.data[3] - v3.data[2]*v2.data[3]) + v1.data[2]*(v2.data[0]*v3.data[3] - v3.data[0]*v2.data[3]) - v1.data[3]*(v2.data[0]*v3.data[2] - v3.data[0]*v2.data[2]);
	result.data[2] =  v1.data[0]*(v2.data[1]*v3.data[3] - v3.data[1]*v2.data[3]) - v1.data[1]*(v2.data[0]*v3.data[3] - v3.data[0]*v2.data[3]) + v1.data[3]*(v2.data[0]*v3.data[1] - v3.data[0]*v2.data[1]);
	result.data[3] = -v1.data[0]*(v2.data[1]*v3.data[2] - v3.data[1]*v2.data[2]) + v1.data[1]*(v2.data[0]*v3.data[2] - v3.data[0]*v2.data[2]) - v1.data[2]*(v2.data[0]*v3.data[1] - v3.data[0]*v2.data[1]);
	result.data[4] = (t1)1;

	return result;
}

/* rot
 * (rotate)
 *
 * This rotates a vector v by an angle of a around the axes
 * that aren't referenced by i and j. So in three space, where
 * x = 0, y = 1, z = 2, ..., if i = y and j = z, then we are
 * rotating around the x axis. If i = x and j = z, then we are
 * rotating around the y axis. If i = x and j = y, then we are
 * rotating around the z axis.
 */
template <class t, int s>
vec<t, s> rot(vec<t, s> v, double a, int i, int j)
{
	vec<t, s> result = v;

	result.data[i] = v.data[i]*cos(a) - v.data[j]*sin(a);
	result.data[j] = v.data[i]*sin(a) + v.data[j]*cos(a);

	return result;
}

/* ror
 * (rotate right)
 *
 * This rotates a vector by the given euler angles defined
 * in a. First, it rotates around the x axis, then the y axis,
 * and so on.
 *
 * x, y, z, ...
 */
template <class t, class at, int s>
vec<t, s> ror(vec<t, s> v, vec <at, s> a)
{
	vec<t, s> result = v;
	vec<t, s> temp = v;

	int ai = 0;
	for (int i = s-1; i >= 0; i--)
		for (int j = i-1; j >= 0; j--)
		{
			temp.data[i] = result.data[i]*cos(a[ai]) - result.data[j]*sin(a[ai]);
			temp.data[j] = result.data[i]*sin(a[ai]) + result.data[j]*cos(a[ai]);
			result = temp;
			ai++;
		}

	return result;
}

/* rol
 * (rotate left)
 *
 * This rotates a vector by the given euler angles defined
 * in a. This rotates in the reverse order of ror.
 *
 * ..., z, y, x
 */
template <class t, class at, int s>
vec<t, s> rol(vec<t, s> v, vec <at, s> a)
{
	vec<t, s> result = v;
	vec<t, s> temp = v;

	int ai = s-1;
	for (int i = 0; i >= s-2; i--)
		for (int j = i+1; j >= s-1; j--)
		{
			temp.data[i] = result.data[i]*cos(a[ai]) - result.data[j]*sin(a[ai]);
			temp.data[j] = result.data[i]*sin(a[ai]) + result.data[j]*cos(a[ai]);
			result = temp;
			ai--;
		}

	return result;
}

/* ror
 * (rotate right)
 *
 * This rotates a vector by the given euler angles defined
 * in a. First, it rotates around the x axis, then the y axis,
 * and so on.
 *
 * x, y, z, ...
 */
template <class t, class at, int s>
vec<t, s> ror3(vec<t, s> v, vec<at, s> a)
{
	vec<t, s> x = v;
	vec<t, s> y;

	y.data[1] = x.data[1]*cos(a.data[0]) - x.data[2]*sin(a.data[0]);
	y.data[2] = x.data[1]*sin(a.data[0]) + x.data[2]*cos(a.data[0]);
	y.data[0] = x.data[0];

	x.data[2] = y.data[2]*cos(a.data[1]) - y.data[0]*sin(a.data[1]);
	x.data[0] = y.data[2]*sin(a.data[1]) + y.data[0]*cos(a.data[1]);
	x.data[1] = y.data[1];

	y.data[0] = x.data[0]*cos(a.data[2]) - x.data[1]*sin(a.data[2]);
	y.data[1] = x.data[0]*sin(a.data[2]) + x.data[1]*cos(a.data[2]);
	y.data[2] = x.data[2];

	return y;
}

/* rol
 * (rotate left)
 *
 * This rotates a vector by the given euler angles defined
 * in a. This rotates in the reverse order of ror.
 *
 * ..., z, y, x
 */
template <class t, class at, int s>
vec<t, s> rol3(vec<t, s> v, vec <at, s> a)
{
	vec<t, s> x = v;
	vec<t, s> y;

	y.data[0] = x.data[0]*cos(a[2]) - x.data[1]*sin(a[2]);
	y.data[1] = x.data[0]*sin(a[2]) + x.data[1]*cos(a[2]);
	y.data[2] = x.data[2];

	x.data[2] = y.data[2]*cos(a[1]) - y.data[0]*sin(a[1]);
	x.data[0] = y.data[2]*sin(a[1]) + y.data[0]*cos(a[1]);
	x.data[1] = y.data[1];

	y.data[1] = x.data[1]*cos(a[0]) - x.data[2]*sin(a[0]);
	y.data[2] = x.data[1]*sin(a[0]) + x.data[2]*cos(a[0]);
	y.data[0] = x.data[0];

	return y;
}

/* slerp
 * (spherical linear interpolation)
 *
 * This calculates a spherical linear interpolation between two
 * vectors v1 and v2 using p as the percentage angle from v1 to
 * v2.
 */
template <class t, int s>
vec<t, s> slerp(vec<t, s> v1, vec<t, s> v2, t p)
{
	double omega = acos((double)dot(v1, v2));
	double somega = sin(omega);
	vec <t, s> ret = v1*sin(omega - p*omega) + v2*sin(p*omega);
	return ret/somega;
}

/* mag
 * (magnitude)
 *
 * Calculates the magnitude of a vector v
 * |v| = sqrt(v夫)
 */
template <class t, int s>
t mag(vec<t, s> v)
{
	return sqrt(mag2(v));
}

/* mag2
 * (magnitude^2)
 *
 * Calculates the squared magnitude of a vector v
 * |v|^2 = v夫
 */
template <class t, int s>
t mag2(vec<t, s> v)
{
	t m = 0;
	for (int i = 0; i < s; i++)
		m += v.data[i]*v.data[i];
	return m;
}

/* mag2
 * (magnitude^2)
 *
 * Calculates the squared magnitude of a vector v
 * |v|^2 = v夫
 */
template <class t>
t mag2(vec<t, 2> v)
{
	return v.data[0]*v.data[0] + v.data[1]*v.data[1];
}

/* mag2
 * (magnitude^2)
 *
 * Calculates the squared magnitude of a vector v
 * |v|^2 = v夫
 */
template <class t>
t mag2(vec<t, 3> v)
{
	return v.data[0]*v.data[0] + v.data[1]*v.data[1] + v.data[2]*v.data[2];
}

/* mag2
 * (magnitude^2)
 *
 * Calculates the squared magnitude of a vector v
 * |v|^2 = v夫
 */
template <class t>
t mag2(vec<t, 4> v)
{
	return v.data[0]*v.data[0] + v.data[1]*v.data[1] + v.data[2]*v.data[2] + v.data[3]*v.data[3];
}

/* dot
 * (dot product)
 *
 * Calculates the dot product of two vectors v1 and v2
 * v1夫2 = (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + ...)
 */
template <class t1, class t2, int s>
t1 dot(vec<t1, s> v1, vec<t2, s> v2)
{
	t1 m = 0;
	int i;

	for (i = 0; i < s; i++)
		m += v1.data[i]*v2.data[i];
	return m;
}

/* dist
 * (distance)
 *
 * Calculates the distance between two vectors v1 and v2
 * |v2 - v1| = sqrt((v2.x - v1.x)^2 + (v2.y - v1.y)^2 + (v2.z - v1.z)^2 + ...)
 */
template <class t1, class t2, int s>
t1 dist(vec<t1, s> v1, vec<t2, s> v2)
{
	return mag(v2 - v1);
}

/* dist2
 * (distance^2)
 *
 * Calculates the squared distance between two vectors v1 and v2
 * |v2 - v1|^2 = ((v2.x - v1.x)^2 + (v2.y - v1.y)^2 + (v2.z - v1.z)^2 + ...)
 */
template <class t1, class t2, int s>
t1 dist2(vec<t1, s> v1, vec<t2, s> v2)
{
	return mag2(v2 - v1);
}

/* dir
 * (direction)
 *
 * Generates a normalized direction vector pointing from v1 to v2.
 * (v2 - v1)/|v2 - v1|
 */
template <class t1, class t2, int s>
vec<t1, s> dir(vec<t1, s> v1, vec<t2, s> v2)
{
	return (v2 - v1)/mag(v2 - v1);
}

}

#endif
