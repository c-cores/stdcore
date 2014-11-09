/*
 * matrix.h
 * Blaze Game Engine v0.11
 *
 * Created by Ned Bingham on January 20, 2011.
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

#include "big.h"
#include "vector.h"

#ifndef matrix_h
#define matrix_h

namespace core
{

template <class t, int v, int h>
struct mat
{
	mat()
	{
		for (int i = 0; i < v; i++)
			this->data[i] = vec<t, h>();
	}

	mat(const char *str)
	{
		char vector[256];
		char last_bracket = ' ';
		int j = 0;
		int k = 0;
		for (int i = 0; str[i] != '\0' && k < v; i++)
		{
			if (str[i] == '[')
			{
				last_bracket = '[';
				j = 0;
			}
			else if (str[i] == ']' && last_bracket == '[')
			{
				last_bracket = ']';
				vector[j++] = '\0';
				data[k++] = vec<t, h>((const char *)vector);
			}
			else
				vector[j++] = str[i];
		}
	}

	template <class t2>
	mat(t2 first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		data[0][0] = first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				data[i][j] = va_arg(arguments, t2);
		va_end(arguments);
	}
	mat(float first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		data[0][0] = first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				data[i][j] = va_arg(arguments, double);
		va_end(arguments);
	}

	~mat()
	{

	}

	vec<t, h> data[v];

	template <class t2, int v2, int h2>
	mat<t, v, h> &operator=(mat<t2, v2, h2> m)
	{
		for (int i = 0; i < min(v, v2); i++)
			data[i] = m[i];
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator+=(mat<t2, v, h> m)
	{
		*this = *this + m;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator-=(mat<t2, v, h> m)
	{
		*this = *this - m;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator*=(mat<t2, h, v> m)
	{
		*this = *this * m;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator/=(mat<t2, h, v> m)
	{
		*this = *this / m;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator+=(t2 f)
	{
		*this = *this + f;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator-=(t2 f)
	{
		*this = *this - f;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator*=(t2 f)
	{
		*this = *this * f;
		return *this;
	}

	template <class t2>
	mat<t, v, h> &operator/=(t2 f)
	{
		*this = *this / f;
		return *this;
	}

	vec<t, h> &operator[](int index)
	{
		return data[index];
	}

	vec<ref<t>, v> operator()(int index)
	{
		vec<ref<t>, v> result;

		for (int i = 0; i < v; i++)
			result[i].value = &(data[i][index]);

		return result;
	}

	mat<ref<t>,v,h> operator()(int a, int b)
	{
		mat<ref<t>, v, h> result;

		for (int i = a; i <= b; i++)
			result.data[i-a] = data[i];
		return result;
	}

	mat<ref<t>,v,h> operator()(int a, int b, int c, int d)
	{
		mat<ref<t>, v, h> result;

		for (int i = a; i <= b; i++)
			result.data[i-a] = data[i](c, d);
		return result;
	}

	mat<t, v-1, h-1> remove(int y, int x)
	{
		mat<t, v-1, h-1> result;
		int i, j, a, b;

		for (i = 0, a = 0; i < v; i == y ? i+=2 : i++, a++)
			for (j = 0, b = 0; j < h; j == x ? j+=2 : i++, b++)
				result[a][b] = data[i][j];

		return result;
	}

	mat<t, v, h> &swapr(int a, int b)
	{
		vec<t, h> temp = data[a];
		data[a] = data[b];
		data[b] = temp;
		return *this;
	}

	mat<t, v, h> &swapc(int a, int b)
	{
		t temp;
		for (int i = 0; i < h; i++)
		{
			temp = data[i].data[a];
			data[i].data[a] = data[i].data[b];
			data[i].data[b] = temp;
		}
		return *this;
	}

	void print(FILE *file)
	{
		for (int i = 0; i < v; i++)
			data[i].print(file);
		fprintf(file, "\n");
	}

	void print()
	{
		print(stdout);
	}
};

template <int v, int h>
struct mat<float, v, h>
{
	mat()
	{
		for (int i = 0; i < v; i++)
			this->data[i] = vec<float, h>();
	}

	mat(const char *str)
	{
		char vector[256];
		char last_bracket = ' ';
		int j = 0;
		int k = 0;
		for (int i = 0; str[i] != '\0' && k < v; i++)
		{
			if (str[i] == '[')
			{
				last_bracket = '[';
				j = 0;
			}
			else if (str[i] == ']' && last_bracket == '[')
			{
				last_bracket = ']';
				vector[j++] = '\0';
				data[k++] = vec<float, h>((const char *)vector);
			}
			else
				vector[j++] = str[i];
		}
	}

	template <class t2>
	mat(t2 first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		data[0][0] = first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				data[i][j] = va_arg(arguments, t2);
		va_end(arguments);
	}

	mat(float first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		data[0][0] = first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				data[i][j] = va_arg(arguments, double);
		va_end(arguments);
	}
	~mat()
	{

	}

	vec<float, h> data[v];

	template <class t2, int v2, int h2>
	mat<float, v, h> &operator=(mat<t2, v2, h2> m)
	{
		for (int i = 0; i < min(v, v2); i++)
			data[i] = m[i];
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator+=(mat<t2, v, h> m)
	{
		*this = *this + m;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator-=(mat<t2, v, h> m)
	{
		*this = *this - m;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator*=(mat<t2, h, v> m)
	{
		*this = *this * m;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator/=(mat<t2, h, v> m)
	{
		*this = *this / m;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator+=(t2 f)
	{
		*this = *this + f;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator-=(t2 f)
	{
		*this = *this - f;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator*=(t2 f)
	{
		*this = *this * f;
		return *this;
	}

	template <class t2>
	mat<float, v, h> &operator/=(t2 f)
	{
		*this = *this / f;
		return *this;
	}

	vec<float, h> &operator[](int index)
	{
		return data[index];
	}

	vec<ref<float>, v> operator()(int index)
	{
		vec<ref<float>, v> result;

		for (int i = 0; i < v; i++)
			result[i].value = &(data[i][index]);

		return result;
	}

	mat<ref<float>,v,h> operator()(int a, int b, int c, int d)
	{
		mat<ref<float>, v, h> result;

		for (int i = a; i <= b; i++)
			result.data[i-a] = data[i](c, d);
		return result;
	}

	mat<float, v-1, h-1> remove(int y, int x)
	{
		mat<float, v-1, h-1> result;
		int i, j, a, b;

		for (i = 0, a = 0; i < v; i == y ? i+=2 : i++, a++)
			for (j = 0, b = 0; j < h; j == x ? j+=2 : i++, b++)
				result[a][b] = data[i][j];

		return result;
	}

	mat<float, v, h> &swapr(int a, int b)
	{
		vec<float, h> temp = data[a];
		data[a] = data[b];
		data[b] = temp;
		return *this;
	}

	mat<float, v, h> &swapc(int a, int b)
	{
		float temp;
		for (int i = 0; i < h; i++)
		{
			temp = data[i].data[a];
			data[i].data[a] = data[i].data[b];
			data[i].data[b] = temp;
		}
		return *this;
	}

	void print(FILE *file)
	{
		for (int i = 0; i < v; i++)
			data[i].print(file);
		fprintf(file, "\n");
	}

	void print()
	{
		print(stdout);
	}
};

template <class t, int v, int h>
mat<t, v, h> operator-(mat<t, v, h> m)
{
	mat<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = -m[i];

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator+(mat<t1, v, h> m1, mat<t2, v, h> m2)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m1[i] + m2[i];

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator-(mat<t1, v, h> m1, mat<t2, v, h> m2)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m1[i] - m2[i];

	return result;
}

template <class t1, class t2, int a, int b, int c>
mat<t1, a, c> operator*(mat<t1, a, b> m1, mat<t2, b, c> m2)
{
	mat<t1, a, c> result;
	vec<t1, c> row;
	int i, j, k;

	for (j = 0; j < a; j++)
		for (i = 0; i < c; i++)
		{
			result[j][i] = 0;
			for (k = 0; k < b; k++)
				result[j][i] += m1[j][k] * m2[k][i];
		}

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator/(mat<t1, v, h> v1, mat<t2, v, v> v2)
{
	return rref(v2)*v1;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator+(t1 f, mat<t2, v, h> m)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = f + m[i];

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator-(t1 f, mat<t2, v, h> m)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = f - m[i];

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator*(t1 f, mat<t2, v, h> m)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = f * m[i];

	return result;
}

template <class t1, class t2, int s>
mat<t1, s, s> operator/(t1 f, mat<t2, s, s> m)
{
	return rref(m)*f;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator+(mat<t1, v, h> m, t2 f)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] + f;

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator-(mat<t1, v, h> m, t2 f)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] - f;

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator*(mat<t1, v, h> m, t2 f)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] * f;

	return result;
}

template <class t1, class t2, int v, int h>
mat<t1, v, h> operator/(mat<t1, v, h> m, t2 f)
{
	mat<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] / f;

	return result;
}

/* trace
 *
 * Calculates the trace of the matrix m.
 */
template <class t, int s>
t trace(mat<t, s, s> m)
{
	t result;
	int i;

	for (i = 0; i < s; i++)
		result += m[i][i];

	return result;
}

/* det
 *
 * Calculates the determinant of an s x s matrix.
 */
template <class t, int s>
t det(mat<t, s, s> m)
{
	int i, j;
	t result = 0;
	for (i = 0, j = 1; i < s; i++, j*=-1)
		if (m[0][i] != 0)
			result += (t)j*m[0][i]*det(m.remove(0, i));
	return result;
}

/* det
 *
 * Calculates the determinant of a 1 x 1 matrix.
 */
template <class t>
t det(mat<t, 1, 1> m)
{
	return m[0][0];
}

/* det
 *
 * Calculates the determinant of a 2 x 2 matrix.
 */
template <class t>
t det(mat<t, 2, 2> m)
{
	return m[0][0]*m[1][1] - m[0][1]*m[1][0];
}

/* det
 *
 * Calculates the determinant of a 3 x 3 matrix.
 */
template <class t>
t det(mat<t, 3, 3> m)
{
	return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) +
		   m[0][1]*(m[1][2]*m[2][0] - m[1][0]*m[2][2]) +
		   m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
}

/* adj
 *
 * Calculates the adjugate matrix of the matrix m.
 */
template <class t, int s>
mat<t, s, s> adj(mat<t, s, s> m)
{
	mat<t, s, s> result;
	int i, j, k, l;

	for (i = 0, k = 1; i < s; i++, k*=-1)
		for (j = 0, l = 1; j < s; j++, l*=-1)
			result[i][j] = (t)(k*l)*det(m.remove(i, j));

	return result;
}

/* T
 *
 * Returns the transpose of the matrix m.
 */
template <class t, int v, int h>
mat<t, h, v> T(mat<t, v, h> m)
{
	mat<t, h, v> result;
	int i, j;

	for (i = 0; i < v; i++)
		for (j = 0; j < h; j++)
			result[i][j] = m[j][i];

	return result;
}

/* I
 *
 * Returns an s-dimensional identity matrix.
 */
template <class t, int s>
mat<t, s, s> I()
{
	mat<t, s, s> result;
	int i;

	for (i = 0; i < s; i++)
		result[i][i] = (t)1;

	return result;
}

/* rref
 *
 * returns the reduced row echelon form of the matrix m.
 */
template <class t, int v, int h>
mat<t, v, h> rref(mat<t, v, h> m)
{
	perror("Error: Function \"rref\" not yet implemented.\n");
}

/* rotate
 *
 * Creates an s x s rotation matrix using the vector v
 * as the rotation components.
 */
template <class t, int s>
mat<t, s, s> rotate(vec<t, s> v)
{
	perror("Error: Function \"rotate\" not yet implemented.\n");
}

/* unrotate
 *
 * The inverse of the rotate function.
 */
template <class t, int s>
mat<t, s, s> unrotate(vec<t, s> v)
{
	perror("Error: Function \"rotate\" not yet implemented.\n");
}

/* translate
 *
 * Creates an s x s translation matrix using the vector v
 * as the translation components.
 */
template <class t, int s>
mat<t, s, s> translate(vec<t, s-1> v)
{
	mat<t, s, s> result;
	int i;

	for (i = 0; i < s-1; i++)
	{
		result[i][i] = (t)1;
		result[i][s-1] = v[i];
	}

	result[s-1][s-1] = (t)1;

	return result;
}

/* untranslate
 *
 * The inverse of the translate function.
 */
template <class t, int s>
mat<t, s, s> untranslate(vec<t, s-1> v)
{
	mat<t, s, s> result;
	int i;

	for (i = 0; i < s-1; i++)
	{
		result[i][i] = (t)1;
		result[i][s-1] = -v[i];
	}

	result[s-1][s-1] = (t)1;

	return result;
}

/* scale
 *
 * Creates an s x s scaling matrix using the vector v
 * as the set of scales in the {x, y, z, ...} directions.
 */
template <class t, int s>
mat<t, s, s> scale(vec<t, s-1> v)
{
	mat<t, s, s> result;
	int i;

	for (i = 0; i < s-1; i++)
		result[i][i] = v[i];

	result[s-1][s-1] = (t)1;

	return result;
}

/* unscale
 *
 * The inverse of the scale function.
 */
template <class t, int s>
mat<t, s, s> unscale(vec<t, s-1> v)
{
	mat<t, s, s> result;
	int i;

	for (i = 0; i < s-1; i++)
		result[i][i] = ((t)1)/v[i];

	result[s-1][s-1] = (t)1;

	return result;
}

/* project
 *
 * Creates an (s+1) x (s+1) matrix for s-dimensional
 * perspective projection.
 */
template <class t, int s>
mat<t, s+1, s+1> project(mat<t, 2, s> d)
{
	perror("Error: Function \"project\" not yet implemented.\n");
}

/* unproject
 *
 * The inverse of the project function.
 */
template <class t, int s>
mat<t, s+1, s+1> unproject(mat<t, 2, s> d)
{
	perror("Error: Function \"unproject\" not yet implemented.\n");
}

}

#endif
