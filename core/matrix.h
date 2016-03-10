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
#include "file.h"
#include "math.h"

#ifndef matrix_h
#define matrix_h

namespace core
{

template <class t, int v, int h>
struct matrix
{
	matrix()
	{
	}

	template <class t2>
	matrix(const t2 m[v*h])
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i][j] = m[i*h + j];
	}

	template <int v2, int h2>
	matrix(matrix<t, v2, h2> m)
	{
		int mv = min(v, v2);
		int mh = min(h, h2);
		for (int i = 0; i < mv; i++)
		{
			for (int j = 0; j < mh; j++)
				rows[i][j] = m.rows[i][j];
			for (int j = mh; j < h2; j++)
				rows[i][j] = 0;
		}
		for (int i = mv; i < v2; i++)
			for (int j = 0; j < h2; j++)
				rows[i][j] = 0;
	}

	matrix(int first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		rows[0][0] = (t)first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				rows[i][j] = (t)va_arg(arguments, int);
		va_end(arguments);
	}

	matrix(double first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		rows[0][0] = (t)first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				rows[i][j] = (t)va_arg(arguments, double);
		va_end(arguments);
	}

	matrix(float first, ...)
	{
		va_list arguments;

		va_start(arguments, first);
		rows[0][0] = (t)first;
		for (int i = 0; i < v; i++)
			for (int j = (i == 0 ? 1 : 0); j < h; j++)
				rows[i][j] = (t)va_arg(arguments, double);
		va_end(arguments);
	}

	~matrix()
	{

	}

	vector<t, h> rows[v];

	template <class t2, int v2, int h2>
	matrix<t, v, h> &operator=(matrix<t2, v2, h2> m)
	{
		int mv = min(v, v2);
		int mh = min(h, h2);
		for (int i = 0; i < mv; i++)
		{
			for (int j = 0; j < mh; j++)
				rows[i][j] = m.rows[i][j];
			for (int j = mh; j < h2; j++)
				rows[i][j] = 0;
		}
		for (int i = mv; i < v2; i++)
			for (int j = 0; j < h2; j++)
				rows[i][j] = 0;
		return *this;
	}

	template <class t2>
	matrix<t, v, h> &operator+=(matrix<t2, v, h> m)
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i].rows[j] += m.rows[i].rows[j];
		return *this;
	}

	template <class t2>
	matrix<t, v, h> &operator-=(matrix<t2, v, h> m)
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i].rows[j] -= m.rows[i].rows[j];
		return *this;
	}

	template <class t1>
	matrix<t, v, h> &operator*=(matrix<t1, v, v> m1)
	{
		*this = *this * m1;
		return *this;
	}

	template <class t1>
	matrix<t, v, h> &operator/=(matrix<t1, v, v> m1)
	{
		*this = *this * rref(m1);
		return *this;
	}

	matrix<t, v, h> &operator+=(t f)
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i].rows[j] += f;
		return *this;
	}

	matrix<t, v, h> &operator-=(t f)
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i].rows[j] -= f;
		return *this;
	}

	matrix<t, v, h> &operator*=(t f)
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i].rows[j] *= f;
		return *this;
	}

	matrix<t, v, h> &operator/=(t f)
	{
		for (int i = 0; i < v; i++)
			for (int j = 0; j < h; j++)
				rows[i].rows[j] /= f;
		return *this;
	}

	vector<t, h> &operator[](int index)
	{
		return rows[index];
	}

	vector<t, h> operator[](int index) const
	{
		return rows[index];
	}

	void set_row(int r, vector<t, h> m)
	{
		rows[r] = m;
	}

	vector<t, h> row(int r) const
	{
		vector<t, h> result;
		for (int i = 0; i < h; i++)
			result[i] = rows[r][i];
		return result;
	}

	template <int s2>
	void set_row(int a, int b, matrix<t, s2, h> m)
	{
		for (int i = a; i < b; i++)
			rows[i] = m.rows[i-a];
	}

	matrix<t,v,h> row(int a, int b) const
	{
		matrix<t, v, h> result;
		for (int i = a; i < b; i++)
			for (int j = 0; j < h; j++)
				result.rows[i-a][j] = rows[i][j];

		for (int i = b-a; i < v; i++)
			for (int j = 0; j < h; j++)
				result.rows[i][j] = 0;

		return result;
	}

	void set_col(int c, vector<t, v> m)
	{
		for (int i = 0; i < v; i++)
			rows[i][c] = m[i];
	}

	vector<t, v> col(int c) const
	{
		vector<t, v> result;

		for (int i = 0; i < v; i++)
			result[i] = rows[i][c];

		return result;
	}

	template <int s2>
	void set_col(int a, int b, matrix<t, s2, v> m)
	{
		for (int i = a; i < b; i++)
			for (int j = 0; j < v; j++)
				rows[j][i] = m.rows[i-a][j];
	}

	matrix<t,v,h> col(int a, int b) const
	{
		matrix<t, v, h> result;

		for (int i = 0; i < v; i++)
			for (int j = a; j < b; j++)
				result.rows[i][j-a] = rows[i][j];

		for (int i = 0; i < v; i++)
			for (int j = b-a; j < h; j++)
				result.rows[i][j] = 0;

		return result;
	}

	template <int v2, int h2>
	void set(int va, int vb, int ha, int hb, matrix<t, v2, h2> m)
	{
		for (int i = va; i < vb; i++)
			for (int j = ha; j < hb; j++)
				rows[i][j] = m.rows[i-va][j-ha];
	}

	matrix<t, v, h> operator()(int va, int vb, int ha, int hb) const
	{
		matrix<t, v, h> result;
		for (int i = va; i < vb; i++)
			for (int j = ha; j < hb; j++)
				result.rows[i-va][j-ha] = rows[i][j];

		for (int i = vb-va; i < v; i++)
			for (int j = 0; j < h; j++)
				result.rows[i][j] = 0;

		for (int i = 0; i < v; i++)
			for (int j = hb-ha; j < h; j++)
				result.rows[i][j] = 0;

		return result;
	}

	matrix<t, v-1, h-1> remove(int y, int x)
	{
		matrix<t, v-1, h-1> result;

		for (int i = 0; i < v-1; i++)
			for (int j = 0; j < h-1; j++)
				result[i][j] = rows[i + (i >= y)][j + (j >= x)];

		return result;
	}

	matrix<t, v, h> &swapr(int a, int b)
	{
		vector<t, h> temp = rows[a];
		rows[a] = rows[b];
		rows[b] = temp;
		return *this;
	}

	matrix<t, v, h> &swapc(int a, int b)
	{
		t temp;
		for (int i = 0; i < h; i++)
		{
			temp = rows[i].rows[a];
			rows[i].rows[a] = rows[i].rows[b];
			rows[i].rows[b] = temp;
		}
		return *this;
	}

	bool is_orthogonal()
	{
		for (int j = 0; j < h; j++)
			for (int i = 0; i < h; i++)
			{
				t total = 0;
				for (int k = 0; k < v; k++)
					total += *this[j][k] * *this[k][i];

				if (total != (t)(i == j))
					return false;
			}

		return true;
	}

	t *data()
	{
		return (t*)rows;
	}
};

template <class t, int v, int h>
file &operator<<(file &f, matrix<t, v, h> m)
{
	for (int i = 0; i < v; i++)
		f << m[i] << endl;
	return f;
}

template <class t, int v, int h>
matrix<t, v, h> operator-(matrix<t, v, h> m)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = -m[i];

	return result;
}

template <class t1, class t2, int v, int h>
matrix<t1, v, h> operator+(matrix<t1, v, h> m1, matrix<t2, v, h> m2)
{
	matrix<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m1[i] + m2[i];

	return result;
}

template <class t1, class t2, int v, int h>
matrix<t1, v, h> operator-(matrix<t1, v, h> m1, matrix<t2, v, h> m2)
{
	matrix<t1, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m1[i] - m2[i];

	return result;
}

template <class t1, class t2, int a, int b, int c>
matrix<t1, a, c> operator*(matrix<t1, a, b> m1, matrix<t2, b, c> m2)
{
	matrix<t1, a, c> result;

	for (int j = 0; j < a; j++)
		for (int i = 0; i < c; i++)
		{
			result[j][i] = 0;
			for (int k = 0; k < b; k++)
				result[j][i] += m1[j][k] * m2[k][i];
		}

	return result;
}

template <class t1, class t2, int v, int h>
matrix<t1, v, h> operator/(matrix<t1, v, h> v1, matrix<t2, v, v> v2)
{
	return rref(v2)*v1;
}

template <class t, int v, int h>
matrix<t, v, h> operator+(t f, matrix<t, v, h> m)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = f + m[i];

	return result;
}

template <class t, int v, int h>
matrix<t, v, h> operator-(t f, matrix<t, v, h> m)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = f - m[i];

	return result;
}

template <class t, int v, int h>
matrix<t, v, h> operator*(t f, matrix<t, v, h> m)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = f * m[i];

	return result;
}

template <class t, int s>
matrix<t, s, s> operator/(t f, matrix<t, s, s> m)
{
	return rref(m)*f;
}

template <class t, int v, int h>
matrix<t, v, h> operator+(matrix<t, v, h> m, t f)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] + f;

	return result;
}

template <class t, int v, int h>
matrix<t, v, h> operator-(matrix<t, v, h> m, t f)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] - f;

	return result;
}

template <class t, int v, int h>
matrix<t, v, h> operator*(matrix<t, v, h> m, t f)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] * f;

	return result;
}

template <class t, int v, int h>
matrix<t, v, h> operator/(matrix<t, v, h> m, t f)
{
	matrix<t, v, h> result;
	for (int i = 0; i < v; i++)
		result[i] = m[i] / f;

	return result;
}

template <class t1, class t2, int a, int b>
vector<t1, a> operator*(matrix<t1, a, b> m1, vector<t2, b> v)
{
	vector<t1, a> result;

	for (int j = 0; j < a; j++)
	{
		result[j] = 0;
		for (int k = 0; k < b; k++)
			result[j] += m1[j][k] * v[k];
	}

	return result;
}

template <class t1, class t2, int a, int b>
vector<t1, a> operator/(vector<t2, b> v, matrix<t1, a, b> m1)
{
	return inverse(m1)*v;
}

/* trace
 *
 * Calculates the trace of the matrix m.
 */
template <class t, int s>
t trace(matrix<t, s, s> m)
{
	t result;

	for (int i = 0; i < s; i++)
		result += m[i][i];

	return result;
}

/* determinant
 *
 * Calculates the determinant of an s x s matrix.
 */
template <class t, int s>
t determinant(matrix<t, s, s> m)
{
	int i, j;
	t result = 0;
	for (i = 0, j = 1; i < s; i++, j*=-1)
		if (m[0][i] != 0)
			result += (t)j*m[0][i]*determinant(m.remove(0, i));
	return result;
}

/* determinant
 *
 * Calculates the determinant of a 1 x 1 matrix.
 */
template <class t>
t determinant(matrix<t, 1, 1> m)
{
	return m[0][0];
}

/* determinant
 *
 * Calculates the determinant of a 2 x 2 matrix.
 */
template <class t>
t determinant(matrix<t, 2, 2> m)
{
	return m[0][0]*m[1][1] - m[0][1]*m[1][0];
}

/* determinant
 *
 * Calculates the determinant of a 3 x 3 matrix.
 */
template <class t>
t determinant(matrix<t, 3, 3> m)
{
	return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1]) +
		   m[0][1]*(m[1][2]*m[2][0] - m[1][0]*m[2][2]) +
		   m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
}

/* adjugate
 *
 * Calculates the adjugate matrix of the matrix m.
 */
template <class t, int s>
matrix<t, s, s> adjugate(matrix<t, s, s> m)
{
	matrix<t, s, s> result;

	for (int i = 0, k = 1; i < s; i++, k*=-1)
		for (int j = 0, l = 1; j < s; j++, l*=-1)
			result[i][j] = (t)(k*l)*determinant(m.remove(i, j));

	return result;
}

/* transpose
 *
 * Returns the transpose of the matrix m.
 */
template <class t, int v, int h>
matrix<t, h, v> transpose(matrix<t, v, h> m)
{
	matrix<t, h, v> result;

	for (int i = 0; i < v; i++)
		for (int j = 0; j < h; j++)
			result[i][j] = m[j][i];

	return result;
}

/* identity
 *
 * Returns a v,h-dimensional identity matrix.
 */
template <class t, int v, int h>
matrix<t, v, h> identity()
{
	matrix<t, v, h> result;

	for (int i = 0; i < v; i++)
		for (int j = 0; j < h; j++)
			result[i][j] = (i == j);

	return result;
}

/* rref
 *
 * returns the reduced row-echelon form of the matrix m.
 *
 * A matrix is in reduced row-echelon form (RREF) if it satisfies all of the following conditions.
 *  1. If a row has nonzero entries, then the first non-zero entry is 1 called the leading 1 in this row.
 *  2. If a column contains a leading one then all other entries in that column are zero.
 *  3. If a row contains a leading one the each row above contains a leading one further to the left.
 * The last point implies that if a matrix in rref has any zero rows they must appear as the
 * last rows of the matrix.
 */
template <class t, int v, int h>
matrix<t, v, h> rref(matrix<t, v, h> m)
{
	int i = 0, j = 0;
	while (i < v && j < h)
	{
		// If m_ij = 0 swap the i-th row with some other row below to guarantee that
		// m_ij != 0. The non-zero entry in the (i, j)-position is called a pivot.
		if (m[i][j] == 0)
		{
			for (int k = 0; k < v; k++)
				if (m[k][j] != 0)
				{
					m.swapr(i, k);
					k = v;
				}
		}

		// If all entries in the column are zero, increase j by 1.
		if (m[i][j] != 0)
		{
			// Divide the i-th row by m_ij to make the pivot entry = 1.
			m[i] /= m[i][j];

			// Eliminate all other entries in the j-th column by subtracting suitable
			// multiples of the i-th row from the other rows.
			for (int k = 0; k < v; k++)
				if (k != i)
					m[k] -= m[i]*m[k][j];

			// Increase i by 1 and j by 1 to choose the new pivot element. Return to Step 1.
			i++;
		}
		j++;
	}
	return m;
}

/* inverse
 *
 * Attempts to invert the matrix: This is not guaranteed to be correct.
 * If the matrix isn't invertible given the value type, then the matrix returned
 * won't be the inverse.
 *
 * A matrix is in reduced row-echelon form (RREF) if it satisfies all of the following conditions.
 *  1. If a row has nonzero entries, then the first non-zero entry is 1 called the leading 1 in this row.
 *  2. If a column contains a leading one then all other entries in that column are zero.
 *  3. If a row contains a leading one the each row above contains a leading one further to the left.
 * The last point implies that if a matrix in rref has any zero rows they must appear as the
 * last rows of the matrix.
 */
template <class t, int v, int h>
matrix<t, v, h> inverse(matrix<t, v, h> m)
{
	matrix<t, v, h> result = identity<t, v, h>();
	int i = 0, j = 0;
	while (i < v && j < h)
	{
		// If m_ij = 0 swap the i-th row with some other row below to guarantee that
		// m_ij != 0. The non-zero entry in the (i, j)-position is called a pivot.
		if (m[i][j] == 0)
		{
			for (int k = 0; k < v; k++)
				if (m[k][j] != 0)
				{
					m.swapr(i, k);
					result.swapr(i, k);
					k = v;
				}
		}

		// If all entries in the column are zero, increase j by 1.
		if (m[i][j] != 0)
		{
			// Divide the i-th row by m_ij to make the pivot entry = 1.
			result[i] /= m[i][j];
			m[i] /= m[i][j];

			// Eliminate all other entries in the j-th column by subtracting suitable
			// multiples of the i-th row from the other rows.
			for (int k = 0; k < v; k++)
				if (k != i)
				{
					result[k] -= result[i]*m[k][j];
					m[k] -= m[i]*m[k][j];
				}

			// Increase i by 1 and j by 1 to choose the new pivot element. Return to Step 1.
			i++;
		}
		j++;
	}
	return result;
}

/* invertible
 *
 * Checks to see if a matrix is invertible
 *
 * A matrix m is invertible if it is square (v = h) and determinant(m) != 0
 */
template <class t, int v, int h>
bool invertible(matrix<t, v, h> m)
{
	if (v != h)
		return false;

	if (determinant(m) == 0)
		return false;

	return true;
}

/* rank
 *
 * returns the number of linearly independent columns
 */
template <class t, int v, int h>
int rank(matrix<t, v, h> m)
{
	int count = 0;
	matrix<t, v, h> check = rref(m);
	for (int i = 0; i < v; i++)
		for (int j = 0; j < h; j++)
			if (check[i][j] != 0)
			{
				count++;
				j = h;
			}
	return count;
}

/* rotate
 *
 * Creates an s x s rotation matrix using the vector v
 * as the rotation components.
 */
template <class t>
matrix<t, 4, 4> rotate(t a, vector<t, 3> v)
{
	t c = cos(a);
	t o = 1-c;
	t s = sin(a);
	t l = mag2(v);

	if (l != 1)
		v /= sqrt(l);

	return matrix<t, 4, 4>(v[0]*v[0]*o + c,      v[0]*v[1]*o - v[2]*s, v[0]*v[2]*o + v[1]*s, 0.0f,
			               v[1]*v[0]*o + v[2]*s, v[1]*v[1]*o + c,      v[1]*v[2]*o - v[0]*s, 0.0f,
						   v[0]*v[2]*o - v[1]*s, v[1]*v[2]*o + v[0]*s, v[2]*v[2]*o + c,      0.0f,
						   0.0f,                 0.0f,                 0.0f,                 1.0f);
}

/* rotate_x
 *
 * Creates an s x s rotation matrix about the x axis.
 */
template <class t>
matrix<t, 4, 4> rotate(t a, int i, int j)
{
	t c = cos(a);
	t s = sin(a);
	matrix<t, 4, 4> result(1.0f, 0.0f, 0.0f, 0.0f,
						   0.0f, 1.0f, 0.0f, 0.0f,
						   0.0f, 0.0f, 1.0f, 0.0f,
						   0.0f, 0.0f, 0.0f, 1.0f);
	result[i][i] = c;
	result[i][j] = -s;
	result[j][i] = s;
	result[j][j] = c;
	return result;
}

template <class t>
matrix<t, 4, 4> rotate_x(t a)
{
	return rotate(a, 1, 2);
}

template <class t>
matrix<t, 4, 4> rotate_y(t a)
{
	return rotate(a, 2, 0);
}

template <class t>
matrix<t, 4, 4> rotate_z(t a)
{
	return rotate(a, 0, 1);
}

template <class t>
matrix<t, 4, 4> rotate_xyz(vector<t, 3> a)
{
	return rotate_x(a[0])*rotate_y(a[1])*rotate_z(a[2]);
}

template <class t>
matrix<t, 4, 4> rotate_zyx(vector<t, 3> a)
{
	return rotate_z(a[2])*rotate_y(a[1])*rotate_x(a[0]);
}

/* translate
 *
 * Creates an s x s translation matrix using the vector v
 * as the translation components.
 */
template <class t, int s>
matrix<t, s+1, s+1> translate(vector<t, s> v)
{
	matrix<t, s+1, s+1> result;

	for (int i = 0; i < s+1; i++)
		for (int j = 0; j < s+1; j++)
			result[i][j] = (i == j);

	for (int i = 0; i < s; i++)
		result[i][s] = v[i];

	return result;
}

/* scale
 *
 * Creates an s x s scaling matrix using the vector v
 * as the set of scales in the {x, y, z, ...} directions.
 */
template <class t, int s>
matrix<t, s+1, s+1> scale(vector<t, s> v)
{
	matrix<t, s+1, s+1> result;

	for (int i = 0; i < s+1; i++)
		for (int j = 0; j < s+1; j++)
			result[i][j] = 0;

	for (int i = 0; i < s; i++)
		result[i][i] = v[i];

	result[s][s] = 1;

	return result;
}

/* frustum
 *
 * Creates an (s+1) x (s+1) matrix for s-dimensional
 * perspective projection.
 */
template <class t>
matrix<t, 4, 4> frustum(t left, t right, t bottom, t top, t front, t back)
{
	return matrix<t, 4, 4>(2.0f*front/(right-left), 0.0f,                   (right+left)/(right-left), 0.0f,
			               0.0f,                   2.0f*front/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
						   0.0f,                   0.0f,                   -(back+front)/(back-front),     -2.0f*back*front/(back-front),
						   0.0f,                   0.0f,                   -1.0f,                        0.0f);
}

/* ortho
 *
 */
template <class t>
matrix<t, 4, 4> ortho(t left, t right, t bottom, t top, t front, t back)
{
	return matrix<t, 4, 4>(2/(right-left), 0,               0,             (right+left)/(right-left),
			               0,              2/(top-bottom),  0,             (top+bottom)/(top-bottom),
						   0,              0,               -2/(back-front), (back+front)/(back-front),
						   0,              0,               0,             1);
}

template <class t>
matrix<t, 3, 3> normal(matrix<t, 4, 4> modelview)
{
	t det = determinant(modelview);
	if (det*det == 1)
		return modelview;
	else
		return transpose(inverse(modelview));
}

}

#endif
