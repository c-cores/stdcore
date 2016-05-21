/*
 * binary_stream.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include "binary_stream.h"

namespace core
{

template <>
binary_stream &operator<<(binary_stream &s1, stream_flush s2)
{
	fwrite(s1.store.data, 1, s1.store.size(), s1.ptr);
	fflush(s1.ptr);
	s1.store.clear();
	return s1;
}

}
