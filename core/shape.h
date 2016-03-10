/*
 * shape.h
 *
 *  Created on: Jul 16, 2015
 *      Author: nbingham
 */

#include "vector.h"

#ifndef shape_h
#define shape_h

namespace core
{

template <class type, int dimension>
struct box
{
	vector<type, dimension> center;
	array<type> size;
};

template <class type, int dimension>
struct ellipse
{
	vector<type, dimension> center;
	array<type> size;
};

}

#endif
