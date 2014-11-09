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


typedef vec<Float,  1>	vec1F;
typedef vec<Float,  2>	vec2F;
typedef vec<Float,  3>	vec3F;
typedef vec<Float,  4>	vec4F;
typedef vec<Float,  5>	vec5F;
typedef vec<Float,  6>	vec6F;
typedef vec<Float,  7>	vec7F;
typedef vec<Float,  8>	vec8F;
typedef vec<Float,  9>	vec9F;
typedef vec<Float,  10>	vec10F;
typedef vec<Float,  11>	vec11F;
typedef vec<Float,  12>	vec12F;

typedef vec<Int,    1>	vec1I;
typedef vec<Int,    2>	vec2I;
typedef vec<Int,    3>	vec3I;
typedef vec<Int,    4>	vec4I;
typedef vec<Int,    5>	vec5I;
typedef vec<Int,    6>	vec6I;
typedef vec<Int,    7>	vec7I;
typedef vec<Int,    8>	vec8I;
typedef vec<Int,    9>	vec9I;
typedef vec<Int,    10>	vec10I;
typedef vec<Int,    11>	vec11I;
typedef vec<Int,    12>	vec12I;

typedef grad<Float,  1>	grad1F;
typedef grad<Float,  2>	grad2F;
typedef grad<Float,  3>	grad3F;
typedef grad<Float,  4>	grad4F;
typedef grad<Float,  5>	grad5F;
typedef grad<Float,  6>	grad6F;
typedef grad<Float,  7>	grad7F;
typedef grad<Float,  8>	grad8F;
typedef grad<Float,  9>	grad9F;
typedef grad<Float,  10>	grad10F;
typedef grad<Float,  11>	grad11F;
typedef grad<Float,  12>	grad12F;

typedef grad<Int,    1>	grad1I;
typedef grad<Int,    2>	grad2I;
typedef grad<Int,    3>	grad3I;
typedef grad<Int,    4>	grad4I;
typedef grad<Int,    5>	grad5I;
typedef grad<Int,    6>	grad6I;
typedef grad<Int,    7>	grad7I;
typedef grad<Int,    8>	grad8I;
typedef grad<Int,    9>	grad9I;
typedef grad<Int,    10>	grad10I;
typedef grad<Int,    11>	grad11I;
typedef grad<Int,    12>	grad12I;

typedef mat<Float,  1, 1>	mat1F;
typedef mat<Float,  2, 2>	mat2F;
typedef mat<Float,  3, 3>	mat3F;
typedef mat<Float,  4, 4>	mat4F;
typedef mat<Float,  5, 5>	mat5F;

typedef mat<Int,  1, 1>	mat1I;
typedef mat<Int,  2, 2>	mat2I;
typedef mat<Int,  3, 3>	mat3I;
typedef mat<Int,  4, 4>	mat4I;
typedef mat<Int,  5, 5>	mat5I;

typedef mat<Float,  1, 2>	frustum1F;
typedef mat<Float,  2, 2>	frustum2F;
typedef mat<Float,  3, 2>	frustum3F;
typedef mat<Float,  4, 2>	frustum4F;
typedef mat<Float,  5, 2>	frustum5F;

typedef mat<Int,    1, 2>	frustum1I;
typedef mat<Int,    2, 2>	frustum2I;
typedef mat<Int,    3, 2>	frustum3I;
typedef mat<Int,    4, 2>	frustum4I;
typedef mat<Int,    5, 2>	frustum5I;

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

}

#endif
