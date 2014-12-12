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

typedef vec<float,  1>	vec1f;
typedef vec<float,  2>	vec2f;
typedef vec<float,  3>	vec3f;
typedef vec<float,  4>	vec4f;
typedef vec<float,  5>	vec5f;
typedef vec<float,  6>	vec6f;
typedef vec<float,  7>	vec7f;
typedef vec<float,  8>	vec8f;
typedef vec<float,  9>	vec9f;
typedef vec<float,  10>	vec10f;
typedef vec<float,  11>	vec11f;
typedef vec<float,  12>	vec12f;

typedef vec<int,    1>	vec1i;
typedef vec<int,    2>	vec2i;
typedef vec<int,    3>	vec3i;
typedef vec<int,    4>	vec4i;
typedef vec<int,    5>	vec5i;
typedef vec<int,    6>	vec6i;
typedef vec<int,    7>	vec7i;
typedef vec<int,    8>	vec8i;
typedef vec<int,    9>	vec9i;
typedef vec<int,    10>	vec10i;
typedef vec<int,    11>	vec11i;
typedef vec<int,    12>	vec12i;

typedef grad<float,  1>	 grad1f;
typedef grad<float,  2>	 grad2f;
typedef grad<float,  3>	 grad3f;
typedef grad<float,  4>	 grad4f;
typedef grad<float,  5>	 grad5f;
typedef grad<float,  6>	 grad6f;
typedef grad<float,  7>	 grad7f;
typedef grad<float,  8>	 grad8f;
typedef grad<float,  9>	 grad9f;
typedef grad<float,  10> grad10f;
typedef grad<float,  11> grad11f;
typedef grad<float,  12> grad12f;

typedef grad<int,    1>	 grad1i;
typedef grad<int,    2>	 grad2i;
typedef grad<int,    3>	 grad3i;
typedef grad<int,    4>	 grad4i;
typedef grad<int,    5>	 grad5i;
typedef grad<int,    6>	 grad6i;
typedef grad<int,    7>	 grad7i;
typedef grad<int,    8>	 grad8i;
typedef grad<int,    9>	 grad9i;
typedef grad<int,    10> grad10i;
typedef grad<int,    11> grad11i;
typedef grad<int,    12> grad12i;

typedef mat<float,  1, 1> mat1f;
typedef mat<float,  2, 2> mat2f;
typedef mat<float,  3, 3> mat3f;
typedef mat<float,  4, 4> mat4f;
typedef mat<float,  5, 5> mat5f;

typedef mat<int,  1, 1>	mat1i;
typedef mat<int,  2, 2>	mat2i;
typedef mat<int,  3, 3>	mat3i;
typedef mat<int,  4, 4>	mat4i;
typedef mat<int,  5, 5>	mat5i;

typedef mat<float,  1, 2>	frustum1f;
typedef mat<float,  2, 2>	frustum2f;
typedef mat<float,  3, 2>	frustum3f;
typedef mat<float,  4, 2>	frustum4f;
typedef mat<float,  5, 2>	frustum5f;

typedef mat<int,    1, 2>	frustum1i;
typedef mat<int,    2, 2>	frustum2i;
typedef mat<int,    3, 2>	frustum3i;
typedef mat<int,    4, 2>	frustum4i;
typedef mat<int,    5, 2>	frustum5i;

typedef vec<poly, 1> field1;
typedef vec<poly, 2> field2;
typedef vec<poly, 3> field3;
typedef vec<poly, 4> field4;
typedef vec<poly, 5> field5;


typedef vec<Real,  1>	vec1F;
typedef vec<Real,  2>	vec2F;
typedef vec<Real,  3>	vec3F;
typedef vec<Real,  4>	vec4F;
typedef vec<Real,  5>	vec5F;
typedef vec<Real,  6>	vec6F;
typedef vec<Real,  7>	vec7F;
typedef vec<Real,  8>	vec8F;
typedef vec<Real,  9>	vec9F;
typedef vec<Real,  10>	vec10F;
typedef vec<Real,  11>	vec11F;
typedef vec<Real,  12>	vec12F;

typedef vec<Integer,    1>	vec1I;
typedef vec<Integer,    2>	vec2I;
typedef vec<Integer,    3>	vec3I;
typedef vec<Integer,    4>	vec4I;
typedef vec<Integer,    5>	vec5I;
typedef vec<Integer,    6>	vec6I;
typedef vec<Integer,    7>	vec7I;
typedef vec<Integer,    8>	vec8I;
typedef vec<Integer,    9>	vec9I;
typedef vec<Integer,    10>	vec10I;
typedef vec<Integer,    11>	vec11I;
typedef vec<Integer,    12>	vec12I;

typedef grad<Real,  1>	grad1F;
typedef grad<Real,  2>	grad2F;
typedef grad<Real,  3>	grad3F;
typedef grad<Real,  4>	grad4F;
typedef grad<Real,  5>	grad5F;
typedef grad<Real,  6>	grad6F;
typedef grad<Real,  7>	grad7F;
typedef grad<Real,  8>	grad8F;
typedef grad<Real,  9>	grad9F;
typedef grad<Real,  10>	grad10F;
typedef grad<Real,  11>	grad11F;
typedef grad<Real,  12>	grad12F;

typedef grad<Integer,    1>	grad1I;
typedef grad<Integer,    2>	grad2I;
typedef grad<Integer,    3>	grad3I;
typedef grad<Integer,    4>	grad4I;
typedef grad<Integer,    5>	grad5I;
typedef grad<Integer,    6>	grad6I;
typedef grad<Integer,    7>	grad7I;
typedef grad<Integer,    8>	grad8I;
typedef grad<Integer,    9>	grad9I;
typedef grad<Integer,    10>	grad10I;
typedef grad<Integer,    11>	grad11I;
typedef grad<Integer,    12>	grad12I;

typedef mat<Real,  1, 1>	mat1F;
typedef mat<Real,  2, 2>	mat2F;
typedef mat<Real,  3, 3>	mat3F;
typedef mat<Real,  4, 4>	mat4F;
typedef mat<Real,  5, 5>	mat5F;

typedef mat<Integer,  1, 1>	mat1I;
typedef mat<Integer,  2, 2>	mat2I;
typedef mat<Integer,  3, 3>	mat3I;
typedef mat<Integer,  4, 4>	mat4I;
typedef mat<Integer,  5, 5>	mat5I;

typedef mat<Real,  1, 2>	frustum1F;
typedef mat<Real,  2, 2>	frustum2F;
typedef mat<Real,  3, 2>	frustum3F;
typedef mat<Real,  4, 2>	frustum4F;
typedef mat<Real,  5, 2>	frustum5F;

typedef mat<Integer,    1, 2>	frustum1I;
typedef mat<Integer,    2, 2>	frustum2I;
typedef mat<Integer,    3, 2>	frustum3I;
typedef mat<Integer,    4, 2>	frustum4I;
typedef mat<Integer,    5, 2>	frustum5I;

typedef vec2F				lineF;
typedef vec3F				circleF;
typedef vec3F				squareF;
typedef vec4F				ovalF;
typedef vec4F				rectangleF;
typedef vec4F				sphereF;
typedef vec4F				cubeF;
typedef vec5F				ellipseF;
typedef vec5F				cuboidF;
typedef vec5F				hypersphereF;
typedef vec5F				hypercubeF;
typedef vec6F				hyperellipseF;
typedef vec6F				tesseractF;

typedef vec2I				lineI;
typedef vec3I				circleI;
typedef vec3I				squareI;
typedef vec4I				ovalI;
typedef vec4I				rectangleI;
typedef vec4I				sphereI;
typedef vec4I				cubeI;
typedef vec5I				ellipseI;
typedef vec5I				cuboidI;
typedef vec5I				hypersphereI;
typedef vec5I				hypercubeI;
typedef vec6I				hyperellipseI;
typedef vec6I				tesseractI;

typedef vec<float, 3> uvw;
typedef vec<float, 2> uv;
typedef vec<float, 4> xyzw;
typedef vec<float, 3> xyz;
typedef vec<unsigned char, 4> rgba;
typedef vec<unsigned char, 3> rgb;
typedef vec<float, 4> rgba_hdr;
typedef vec<float, 3> rgb_hdr;

template <class type, int n>
struct space
{
	space()
	{
		for (int i = 0; i < n; i++)
			axis[i][i] = (type)1.0;
	}

	template <class angle_type>
	space(vec<angle_type, n> angle, bool ror = true)
	{
		if (ror)
			for (int i = 0; i < n; i++)
			{
				axis[i][i] = (type)1.0;
				axis[i] = core::ror(axis[i], angle);
			}
		else
			for (int i = 0; i < n; i++)
			{
				axis[i][i] = (type)1.0;
				axis[i] = core::rol(axis[i], angle);
			}
	}

	~space()
	{

	}

	vec<type, n> axis[n];

	template <class angle_type>
	void ror(vec<angle_type, n> angle)
	{
		for (int i = 0; i < n; i++)
			axis[i] = core::ror(axis[i], angle);
	}

	template <class angle_type>
	void rol(vec<angle_type, n> angle)
	{
		for (int i = 0; i < n; i++)
			axis[i] = core::rol(axis[i], angle);
	}

	template <class input_type>
	vec<type, n> tranform(vec<input_type, n> v)
	{
		vec<type, n> result;
		for (int i = 0; i < n; i++)
			result += v[i]*axis[i];
		return result;
	}
};

}

#endif
