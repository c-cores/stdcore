/*
 * search.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>
#include <core/range.h>

namespace core
{

template <typename container, typename element>
typename container::iterator find_first(container &c, const element &t)
{
	for (typename container::iterator i = c.begin(); i; i++)
		if (*i == t)
			return i;

	return c.end();
}

template <typename container, typename element>
typename container::iterator find_last(container &c, const element &t)
{
	for (typename container::iterator i = c.rbegin(); i != c.rend(); i--)
		if (*i == t)
			return i;

	return c.end();
}

template <typename container, typename container2, typename element>
container2 find_all(container &c, const element &t)
{
	container2 results;
	for (typename container::iterator i = c.begin(); i; i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container1, typename container2>
typename container1::iterator find_first_of(container1 c1, const container2 &c2)
{
	for (typename container1::iterator i = c1.begin(); i; i++)
		for (typename container2::const_iterator j = c2.begin(); j; j++)
			if (*i == *j)
				return i;

	return c1.end();
}

template <typename container1, typename container2>
typename container1::iterator find_last_of(container1 c1, const container2 &c2)
{
	for (typename container1::iterator i = c1.rbegin(); i; i--)
		for (typename container2::const_iterator j = c2.begin(); j; j++)
			if (*i == *j)
				return i;

	return c1.end();
}

template <typename container, typename container2, typename container3>
container2 find_all_of(container &c, const container3 &c2)
{
	container2 results;
	for (typename container::iterator i = c.begin(); i; i++)
		for (typename container3::const_iterator j = c2.begin(); j; j++)
		if (*i == *j)
			results.push_back(i);

	return results;
}

template <typename container, typename container2>
typename container::iterator find_first_pattern(container &c, const container2 &t)
{
	for (typename container::iterator i = c.begin(); i; i++)
	{
		bool found = true;
		typename container::iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j && found; j++,k++)
		{
			if (k == c.end())
				return c.end();
			else
				found = (*k == *j);
		}

		if (found)
			return i;
	}

	return c.end();
}

template <typename container, typename container2>
typename container::iterator find_last_pattern(container &c, const container2 &t)
{
	for (typename container::iterator i = c.rbegin(); i != c.rend(); i--)
	{
		bool found = true;
		typename container::iterator k = i;
		for (typename container2::const_iterator j = t.rbegin(); j != t.rend() && found; j--,k--)
		{
			if (k == c.rend())
				return c.rend();
			else
				found = (*k == *j);
		}

		if (found)
			return i;
	}

	return c.rend();
}

template <typename container, typename container2, typename container3>
container2 find_all_pattern(container &c, const container3 &t)
{
	container2 result;
	for (typename container::iterator i = c.rbegin(); i != c.rend(); i--)
	{
		bool found = true;
		typename container::iterator k = i;
		for (typename container3::const_iterator j = t.rbegin(); j != t.rend() && found; j--,k--)
		{
			if (k == c.rend())
				return result;
			else
				found = (*k == *j);
		}

		if (found)
			result.push_back(i);
	}

	return result;
}

template <typename container, typename element>
typename container::iterator search_tree(container c, const element &t, int radix = 2)
{
	int size = c.end() - c.begin();
	if (size >= radix)
	{
		int D = 2*radix - size;
		slice<range<typename container::iterator, int> > pivot(c.begin(), c.begin());
		while (pivot.finish)
		{
			if (D > 0)
			{
				if (t <= *pivot.finish)
					return search_tree(pivot, t, radix);
				pivot.start = pivot.finish+1;
				D += 2*radix - 2*size;
			}
			else
				D += 2*radix;

			pivot.finish++;
		}

		return search_tree(pivot, t, radix);
	}
	else
	{
		typename slice<container>::iterator i = c.begin();
		while (i && *i < t)
			i++;
		return i;
	}
}

}

