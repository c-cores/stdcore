/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include "sort.h"
#include "search.h"

namespace core
{

template <class container>
container &collapse(container &c)
{
	typename container::iterator i = c.begin(), j = c.begin()+1;
	for (; j != c.end(); j++)
		if (!(*i == *j) && ++i != j)
			*i = *j;

	if (++i != c.end())
		i.chop();

	return c;
}

template <class container>
container &unique(container &c)
{
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		for (typename container::iterator j = i+1; j != c.end();)
		{
			if (*i == *j)
				j.drop();
			else
				j++;
		}

	return c;
}

array<int> range(int lower, int upper, int step = 1)
{
	array<int> result;
	result.reserve((upper-lower)/step);
	for (int i = lower; i < upper; i+=step)
		result.push_back(i);
	return result;
}

}

