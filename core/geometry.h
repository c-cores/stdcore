/*
 * geometry.h
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
#include "complex.h"
#include "vector.h"
#include "matrix.h"
#include "poly.h"
#include "gradient.h"

#ifndef geometry_h
#define geometry_h

namespace core
{
typedef complex<float>  complexf;
typedef complex<int>	complexi;

typedef vector<Real,  1>	vec1F;
typedef vector<Real,  2>	vec2F;
typedef vector<Real,  3>	vec3F;
typedef vector<Real,  4>	vec4F;
typedef vector<Real,  5>	vec5F;
typedef vector<Real,  6>	vec6F;
typedef vector<Real,  7>	vec7F;
typedef vector<Real,  8>	vec8F;
typedef vector<Real,  9>	vec9F;
typedef vector<Real,  10>	vec10F;
typedef vector<Real,  11>	vec11F;
typedef vector<Real,  12>	vec12F;

typedef vector<Integer,    1>	vec1I;
typedef vector<Integer,    2>	vec2I;
typedef vector<Integer,    3>	vec3I;
typedef vector<Integer,    4>	vec4I;
typedef vector<Integer,    5>	vec5I;
typedef vector<Integer,    6>	vec6I;
typedef vector<Integer,    7>	vec7I;
typedef vector<Integer,    8>	vec8I;
typedef vector<Integer,    9>	vec9I;
typedef vector<Integer,    10>	vec10I;
typedef vector<Integer,    11>	vec11I;
typedef vector<Integer,    12>	vec12I;

typedef vector<double,  1>	vec1d;
typedef vector<double,  2>	vec2d;
typedef vector<double,  3>	vec3d;
typedef vector<double,  4>	vec4d;
typedef vector<double,  5>	vec5d;
typedef vector<double,  6>	vec6d;
typedef vector<double,  7>	vec7d;
typedef vector<double,  8>	vec8d;
typedef vector<double,  9>	vec9d;
typedef vector<double,  10>	vec10d;
typedef vector<double,  11>	vec11d;
typedef vector<double,  12>	vec12d;

typedef vector<float,  1>	vec1f;
typedef vector<float,  2>	vec2f;
typedef vector<float,  3>	vec3f;
typedef vector<float,  4>	vec4f;
typedef vector<float,  5>	vec5f;
typedef vector<float,  6>	vec6f;
typedef vector<float,  7>	vec7f;
typedef vector<float,  8>	vec8f;
typedef vector<float,  9>	vec9f;
typedef vector<float,  10>	vec10f;
typedef vector<float,  11>	vec11f;
typedef vector<float,  12>	vec12f;

typedef vector<int,    1>	vec1i;
typedef vector<int,    2>	vec2i;
typedef vector<int,    3>	vec3i;
typedef vector<int,    4>	vec4i;
typedef vector<int,    5>	vec5i;
typedef vector<int,    6>	vec6i;
typedef vector<int,    7>	vec7i;
typedef vector<int,    8>	vec8i;
typedef vector<int,    9>	vec9i;
typedef vector<int,    10>	vec10i;
typedef vector<int,    11>	vec11i;
typedef vector<int,    12>	vec12i;

typedef gradient<Real,  1>	grad1F;
typedef gradient<Real,  2>	grad2F;
typedef gradient<Real,  3>	grad3F;
typedef gradient<Real,  4>	grad4F;
typedef gradient<Real,  5>	grad5F;
typedef gradient<Real,  6>	grad6F;
typedef gradient<Real,  7>	grad7F;
typedef gradient<Real,  8>	grad8F;
typedef gradient<Real,  9>	grad9F;
typedef gradient<Real,  10>	grad10F;
typedef gradient<Real,  11>	grad11F;
typedef gradient<Real,  12>	grad12F;

typedef gradient<Integer,    1>	 grad1I;
typedef gradient<Integer,    2>	 grad2I;
typedef gradient<Integer,    3>	 grad3I;
typedef gradient<Integer,    4>	 grad4I;
typedef gradient<Integer,    5>	 grad5I;
typedef gradient<Integer,    6>	 grad6I;
typedef gradient<Integer,    7>	 grad7I;
typedef gradient<Integer,    8>	 grad8I;
typedef gradient<Integer,    9>	 grad9I;
typedef gradient<Integer,    10> grad10I;
typedef gradient<Integer,    11> grad11I;
typedef gradient<Integer,    12> grad12I;

typedef gradient<double,  1>  grad1d;
typedef gradient<double,  2>  grad2d;
typedef gradient<double,  3>  grad3d;
typedef gradient<double,  4>  grad4d;
typedef gradient<double,  5>  grad5d;
typedef gradient<double,  6>  grad6d;
typedef gradient<double,  7>  grad7d;
typedef gradient<double,  8>  grad8d;
typedef gradient<double,  9>  grad9d;
typedef gradient<double,  10> grad10d;
typedef gradient<double,  11> grad11d;
typedef gradient<double,  12> grad12d;

typedef gradient<float,  1>	 grad1f;
typedef gradient<float,  2>	 grad2f;
typedef gradient<float,  3>	 grad3f;
typedef gradient<float,  4>	 grad4f;
typedef gradient<float,  5>	 grad5f;
typedef gradient<float,  6>	 grad6f;
typedef gradient<float,  7>	 grad7f;
typedef gradient<float,  8>	 grad8f;
typedef gradient<float,  9>	 grad9f;
typedef gradient<float,  10> grad10f;
typedef gradient<float,  11> grad11f;
typedef gradient<float,  12> grad12f;

typedef gradient<int,    1>	 grad1i;
typedef gradient<int,    2>	 grad2i;
typedef gradient<int,    3>	 grad3i;
typedef gradient<int,    4>	 grad4i;
typedef gradient<int,    5>	 grad5i;
typedef gradient<int,    6>	 grad6i;
typedef gradient<int,    7>	 grad7i;
typedef gradient<int,    8>	 grad8i;
typedef gradient<int,    9>	 grad9i;
typedef gradient<int,    10> grad10i;
typedef gradient<int,    11> grad11i;
typedef gradient<int,    12> grad12i;

template <class t, int s>
gradient<t, s> input_grad(t c, int i)
{
	gradient<t, s> result;
	result.elems[s] = c;
	result.elems[i] = (t)1;
	return result;
}

template <class t, int s>
vector<gradient<t, s>, s> input_gvec(vector<t, s> c)
{
	vector<gradient<t, s>, s> result;
	for (int i = 0; i < s; i++)
		result.elems[i] = input_grad<t, s>(c[i], i);
	return result;
}

typedef vector<gradient<float, 1>, 1> gvec1f;
typedef vector<gradient<float, 2>, 2> gvec2f;
typedef vector<gradient<float, 3>, 3> gvec3f;
typedef vector<gradient<float, 4>, 4> gvec4f;
typedef vector<gradient<float, 5>, 5> gvec5f;
typedef vector<gradient<float, 6>, 6> gvec6f;
typedef vector<gradient<float, 7>, 7> gvec7f;
typedef vector<gradient<float, 8>, 8> gvec8f;
typedef vector<gradient<float, 9>, 9> gvec9f;
typedef vector<gradient<float, 10>, 10> gvec10f;
typedef vector<gradient<float, 11>, 11> gvec11f;
typedef vector<gradient<float, 12>, 12> gvec12f;

typedef matrix<Real,  1, 1>	mat1F;
typedef matrix<Real,  2, 2>	mat2F;
typedef matrix<Real,  3, 3>	mat3F;
typedef matrix<Real,  4, 4>	mat4F;
typedef matrix<Real,  5, 5>	mat5F;

typedef matrix<Integer,  1, 1>	mat1I;
typedef matrix<Integer,  2, 2>	mat2I;
typedef matrix<Integer,  3, 3>	mat3I;
typedef matrix<Integer,  4, 4>	mat4I;
typedef matrix<Integer,  5, 5>	mat5I;

typedef matrix<double,  1, 1> mat1d;
typedef matrix<double,  2, 2> mat2d;
typedef matrix<double,  3, 3> mat3d;
typedef matrix<double,  4, 4> mat4d;
typedef matrix<double,  5, 5> mat5d;

typedef matrix<float,  1, 1> mat1f;
typedef matrix<float,  2, 2> mat2f;
typedef matrix<float,  3, 3> mat3f;
typedef matrix<float,  4, 4> mat4f;
typedef matrix<float,  5, 5> mat5f;

typedef matrix<int,  1, 1>	mat1i;
typedef matrix<int,  2, 2>	mat2i;
typedef matrix<int,  3, 3>	mat3i;
typedef matrix<int,  4, 4>	mat4i;
typedef matrix<int,  5, 5>	mat5i;

typedef vector<poly, 1> field1;
typedef vector<poly, 2> field2;
typedef vector<poly, 3> field3;
typedef vector<poly, 4> field4;
typedef vector<poly, 5> field5;


typedef vector<float, 3> uvw;
typedef vector<float, 2> uv;
typedef vector<float, 4> xyzw;
typedef vector<float, 3> xyz;
typedef vector<unsigned char, 4> rgba;
typedef vector<unsigned char, 3> rgb;
typedef vector<float, 4> rgba_hdr;
typedef vector<float, 3> rgb_hdr;

}

#endif
