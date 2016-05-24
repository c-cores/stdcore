/*
 * search.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>

namespace core
{

template <typename container, typename element>
typename slice<container>::iterator find_first(slice<container> c, const element &t)
{
	for (typename slice<container>::iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			return i;

	return c.end();
}

template <typename container, typename element>
typename slice<container>::iterator find_last(slice<container> c, const element &t)
{
	for (typename slice<container>::iterator i = c.rbegin(); i != c.rend(); i--)
		if (*i == t)
			return i;

	return c.end();
}

template <typename container1, typename container2>
typename slice<container1>::iterator find_first_of(slice<container1> c1, const container2 &c2)
{
	for (typename slice<container1>::iterator i = c1.begin(); i != c1.end(); i++)
		for (typename container2::const_iterator j = c2.begin(); j != c2.end(); j++)
			if (*i == *j)
				return i;

	return c1.end();
}

template <typename container1, typename container2>
typename slice<container1>::iterator find_last_of(slice<container1> c1, const container2 &c2)
{
	for (typename slice<container1>::iterator i = c1.rbegin(); i != c1.rend(); i--)
		for (typename container2::const_iterator j = c2.begin(); j != c2.end(); j++)
			if (*i == *j)
				return i;

	return c1.end();
}

template <typename container1, typename container2>
typename slice<container1>::iterator find_pattern(slice<container1> c, const container2 &t)
{
	for (typename slice<container1>::iterator i = c.begin(); i != c.end(); i++)
	{
		bool fail = false;
		typename slice<container1>::iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end(); j++,k++)
		{
			if (k == c.end())
				return c.end();
			else
				fail = (*k != *j);
		}

		if (!fail)
			return i;
	}

	return c.end();
}

template <typename container, typename element>
bool contains(slice<container> c, const element &t)
{
	return (find_first(c, t) != c.end());
}

template <typename container1, typename container2>
bool contains_one_of(slice<container1> c1, const container2 &c2)
{
	return (find_first_of(c1, c2) != c1.end());
}

template <typename container1, typename container2>
bool contains_pattern(slice<container1> c, const container2 &t)
{
	return (find_pattern(c, t) != c.end());
}

template <typename container, typename element>
typename slice<container>::iterator search_tree(slice<container> c, const element &t, int radix = 2)
{
	int size = c.end() - c.begin();
	if (size >= radix)
	{
		int D = 2*radix - size;
		slice<container> pivot(c.begin(), c.begin());
		while (pivot.right != c.end())
		{
			if (D > 0)
			{
				if (t <= *pivot.right)
					return search_tree(pivot, t, radix);
				pivot.left = pivot.right+1;
				D += 2*radix - 2*size;
			}
			else
				D += 2*radix;

			pivot.right++;
		}

		return search_tree(pivot, t, radix);
	}
	else
	{
		typename slice<container>::iterator i = c.begin();
		while (i != c.end() && *i < t)
			i++;
		return i;
	}
}

}

