/*
 * search.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>
#include <core/array.h>

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
typename container::const_iterator find_first(const container &c, const element &t)
{
	for (typename container::const_iterator i = c.begin(); i; i++)
		if (*i == t)
			return i;

	return c.end();
}

template <typename container, typename element>
bool contains(const container &c, const element &t)
{
	return (find_first(c, t) != c.end());
}

template <typename container, typename element>
typename container::iterator find_last(container &c, const element &t)
{
	for (typename container::iterator i = c.rbegin(); i != c.rend(); i--)
		if (*i == t)
			return i;

	return c.rend();
}

template <typename container, typename element>
typename container::const_iterator find_last(const container &c, const element &t)
{
	for (typename container::const_iterator i = c.rbegin(); i != c.rend(); i--)
		if (*i == t)
			return i;

	return c.rend();
}

template <typename container, typename element>
array<typename container::iterator> find_all(container &c, const element &t)
{
	array<typename container::iterator> results;
	for (typename container::iterator i = c.begin(); i; i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container, typename element>
array<typename container::const_iterator> find_all(const container &c, const element &t)
{
	array<typename container::const_iterator> results;
	for (typename container::const_iterator i = c.begin(); i; i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container1, typename container2>
typename container1::iterator find_first_of(container1 &c1, const container2 &c2)
{
	for (typename container1::iterator i = c1.begin(); i; i++)
		if (contains(c2, *i))
			return i;

	return c1.end();
}

template <typename container1, typename container2>
typename container1::const_iterator find_first_of(const container1 &c1, const container2 &c2)
{
	for (typename container1::const_iterator i = c1.begin(); i; i++)
		if (contains(c2, *i))
			return i;

	return c1.end();
}

template <typename container, typename element>
bool contains_one_of(const container &c, const element &t)
{
	return (find_first_of(c, t) != c.end());
}

template <typename container1, typename container2>
typename container1::iterator find_last_of(container1 &c1, const container2 &c2)
{
	for (typename container1::iterator i = c1.rbegin(); i; i--)
		if (contains(c2, *i))
			return i;

	return c1.rend();
}

template <typename container1, typename container2>
typename container1::const_iterator find_last_of(const container1 &c1, const container2 &c2)
{
	for (typename container1::const_iterator i = c1.rbegin(); i; i--)
		if (contains(c2, *i))
			return i;

	return c1.rend();
}

template <typename container, typename container2>
array<typename container::iterator> find_all_of(container &c, const container2 &c2)
{
	array<typename container::iterator> results;
	for (typename container::iterator i = c.begin(); i; i++)
		if (contains(c2, *i))
			results.push_back(i);

	return results;
}

template <typename container, typename container2>
array<typename container::const_iterator> find_all_of(const container &c, const container2 &c2)
{
	array<typename container::const_iterator> results;
	for (typename container::const_iterator i = c.begin(); i; i++)
		if (contains(c2, *i))
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
typename container::const_iterator find_first_pattern(const container &c, const container2 &t)
{
	for (typename container::const_iterator i = c.begin(); i; i++)
	{
		bool found = true;
		typename container::const_iterator k = i;
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
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
			found = (k != c.end()) && (*k == *j);

		if (found)
			return i;
	}

	return c.rend();
}

template <typename container, typename container2>
typename container::const_iterator find_last_pattern(const container &c, const container2 &t)
{
	for (typename container::const_iterator i = c.rbegin(); i != c.rend(); i--)
	{
		bool found = true;
		typename container::const_iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
			found = (k != c.end()) && (*k == *j);

		if (found)
			return i;
	}

	return c.rend();
}

template <typename container, typename container2>
array<typename container::iterator> find_all_pattern(container &c, const container2 &t)
{
	array<typename container::iterator> result;
	for (typename container::iterator i = c.begin(); i; i++)
	{
		bool found = true;
		typename container::iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j && found; j++,k++)
		{
			if (k == c.end())
				return result;
			else
				found = (*k == *j);
		}

		if (found)
			result.push_back(i);
	}

	return result;
}

template <typename container, typename container2>
array<typename container::iterator> find_all_pattern(const container &c, const container2 &t)
{
	array<typename container::iterator> result;
	for (typename container::const_iterator i = c.begin(); i; i++)
	{
		bool found = true;
		typename container::const_iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j && found; j++,k++)
		{
			if (k == c.end())
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
typename container::iterator search_tree(container &c, const element &t, int radix = 2)
{
	int size = c.end() - c.begin();
	if (size >= radix)
	{
		int D = 2*radix - size;
		typename container::iterator start = c.begin();
		typename container::iterator finish = c.begin();
		while (finish)
		{
			if (D > 0)
			{
				if (t <= *finish)
					return search_tree(c.sub(start, finish), t, radix);
				start = finish+1;
				D += 2*radix - 2*size;
			}
			else
				D += 2*radix;

			finish++;
		}

		return search_tree(c.sub(start, finish), t, radix);
	}
	else
	{
		typename container::iterator i = c.begin();
		while (i && *i < t)
			i++;
		return i;
	}
}

template <typename container, typename element>
typename container::const_iterator search_tree(const container &c, const element &t, int radix = 2)
{
	int size = c.end() - c.begin();
	if (size >= radix)
	{
		int D = 2*radix - size;
		typename container::const_iterator start = c.begin();
		typename container::const_iterator finish = c.begin();
		while (finish)
		{
			if (D > 0)
			{
				if (t <= *finish)
					return search_tree(c.sub(start, finish), t, radix);
				start = finish+1;
				D += 2*radix - 2*size;
			}
			else
				D += 2*radix;

			finish++;
		}

		return search_tree(c.sub(start, finish), t, radix);
	}
	else
	{
		typename container::const_iterator i = c.begin();
		while (i && *i < t)
			i++;
		return i;
	}
}

}

