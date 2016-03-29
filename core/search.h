/*
 * search.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include "slice.h"

namespace core
{

template <class container, class element>
typename container::iterator find(container &c, const element &t)
{
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			return i;

	return c.end();
}

template <class container1, class container2>
typename container1::iterator find(container1 &c, const container2 &t)
{
	for (typename container1::iterator i = c.begin(); i != c.end(); i++)
	{
		bool fail = false;
		typename container1::iterator k = i;
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

template <class container, class element>
bool contains(container &c, const element &t)
{
	return (find(c, t) != c.end());
}

template <class container1, class container2>
bool contains(container1 &c, const container2 &t)
{
	return (find(c, t) != c.end());
}

template <class container, class element>
typename container::iterator search_tree(container &c, const element &t, int radix = 2)
{
	int size = c.end() - c.begin();
	if (size >= radix)
	{
		int D = 2*radix - size;
		slice<typename container::iterator> pivot(c.begin(), c.begin());
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
		typename container::iterator i = c.begin();
		while (i != c.end() && *i < t)
			i++;
		return i;
	}
}

}

