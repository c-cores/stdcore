/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include "slice.h"

namespace core
{

template <class container>
container collapse(container c)
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
container unique(container c)
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

template <class container>
container remove(container c, const typename container::type &value)
{
	typename container::iterator i = c.begin();
	while (i != c.end())
	{
		if (*i == value)
			i.drop();
		else
			i++;
	}
	return c;
}

template <class container>
container range(typename container::type lower, typename container::type upper, typename container::type step)
{
	if (lower < upper)
	{
		container result;
		for (typename container::type i = lower; i < upper; i += step)
			result.push_back(i);
		return result;
	}
	else
	{
		container result;
		for (typename container::type i = lower; i > upper; i += step)
			result.push_back(i);
		return result;
	}
}


}

