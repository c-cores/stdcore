/*
 * binary_stream.h
 *
 *  Created on: Feb 5, 2014
 *      Author: nbingham
 */

#include <core/bits.h>
#include <core/stream.h>

#pragma once

namespace core
{

struct binary_stream
{
	binary_stream()
	{
		ptr = NULL;
	}

	binary_stream(const char *filename)
	{
		ptr = fopen(filename, "w");
	}

	binary_stream(FILE *ptr)
	{
		this->ptr = ptr;
	}

	~binary_stream()
	{
		if (ptr != NULL)
			fclose(ptr);
		ptr = NULL;
	}

	FILE *ptr;
	bits store;
};

template <typename type>
inline binary_stream &operator<<(binary_stream &s1, type s2)
{
	s1.store << s2;
	return s1;
}

template <>
binary_stream &operator<<(binary_stream &s1, stream_flush s2);

}

