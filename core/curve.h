/*
 * curve.h
 *
 *  Created on: Jul 11, 2015
 *      Author: nbingham
 */

#include "gradient.h"

#ifndef curve_h
#define curve_h

namespace core
{

template <class type>
type hermit(type p0, type p1, type m0, type m1, float t)
{
	float t2 = t*t;
	float t3 = t2*t;

	return (2.0*t3 - 3.0*t2 + 1)*p0 + (t3 - 2.0*t2 + t)*m0 + (-2.0*t3 + 3.0*t2)*p1 + (t3 - t2)*m1;
}

template <class type>
type hermit1(type p0, type p1, type m0, type m1, float t)
{
	float t2 = t*t;
	float t3 = t2*t;

	return (6.0*t2 - 6.0*t)*p0 + (3.0*t2 - 4.0*t + 1)*m0 + (-6.0*t2 + 6.0*t)*p1 + (3.0*t2 - 2.0*t)*m1;
}

template <class type>
type hermit2(type p0, type p1, type m0, type m1, float t)
{
	float t2 = t*t;
	float t3 = t2*t;

	return (12.0*t - 6.0)*p0 + (6.0*t - 4.0)*m0 + (-12.0*t + 6.0)*p1 + (6.0*t - 2.0)*m1;
}

template <class type>
type hermit3(type p0, type p1, type m0, type m1, float t)
{
	float t2 = t*t;
	float t3 = t2*t;

	return 12.0*p0 + 6.0*m0 + -12.0*p1 + 6.0*m1;
}

}

#endif
