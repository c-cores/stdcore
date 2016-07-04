/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>

namespace core
{

template <class type>
void swap(type &t1, type &t2)
{
	type temp = t1;
	t1 = t2;
	t2 = temp;
}

template <class type>
type median_iterator(type t1, type t2, type t3)
{
	if (*t1 < *t2)
	{
		if (*t2 < *t3)
			return t2;
		else if (*t3 < *t1)
			return t1;
		else
			return t3;
	}
	else
	{
		if (*t1 < *t3)
			return t1;
		else if (*t3 < *t2)
			return t2;
		else
			return t3;
	}
}

// Sorting Algorithms
template <class container>
container sort_selection(container c)
{
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
	{
		typename container::iterator max_j = i;
		for (typename container::iterator j = i+1; j != c.end(); j++)
			if (*j < *max_j)
				max_j = j;

		i.swap(max_j);
	}

	return c;
}

template <class container>
container sort_quick(container c)
{
	if (c.size() > 2)
	{
		typename container::iterator pivot = median_iterator(c.begin(), c.begin() + c.size()/2, c.rbegin());

		pivot.swap(c.rbegin());
		pivot = c.rbegin();

		typename container::iterator store = c.begin();
		for (typename container::iterator i = c.begin(); i != c.rbegin(); i++)
			if (*i < *pivot)
			{
				i.swap(store);
				store++;
			}

		store.swap(c.rbegin());

		sort_quick(c.sub(c.begin(), store));
		sort_quick(c.sub(store+1, c.end()));
	}
	else if (c.size() > 1)
		if (*c.rbegin() < *c.begin())
			c.begin().swap(c.rbegin());

	return c;
}

template <class container>
bool is_sorted(const container &c)
{
	for (typename container::const_iterator i = c.begin(); i != c.rbegin(); i++)
		if (*(i+1) < *i)
			return false;

	return true;
}

template <class container>
bool is_rsorted(const container &c)
{
	for (typename container::const_iterator i = c.begin(); i != c.rbegin(); i++)
		if (*(i+1) > *i)
			return false;

	return true;
}

template <class container>
container reverse(container c)
{
	for (typename container::iterator i = c.begin(), j = c.rbegin(); i != j && i != j+1; i++, j--)
		i.swap(j);
	return c;
}

}

