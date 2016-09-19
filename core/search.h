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
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			return i;

	return c.end();
}

template <typename container, typename element>
typename container::const_iterator find_first(const container &c, const element &t)
{
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
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
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container, typename element>
array<typename container::const_iterator> find_all(const container &c, const element &t)
{
	array<typename container::const_iterator> results;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container, typename element>
int count_all(const container &c, const element &t)
{
	int result = 0;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		result += (*i == t);
	return result;
}

template <typename container1, typename container2>
typename container1::iterator find_first_of(container1 &c1, const container2 &c2)
{
	for (typename container1::iterator i = c1.begin(); i != c1.end(); i++)
		if (contains(c2, *i))
			return i;

	return c1.end();
}

template <typename container1, typename container2>
typename container1::const_iterator find_first_of(const container1 &c1, const container2 &c2)
{
	for (typename container1::const_iterator i = c1.begin(); i != c1.end(); i++)
		if (contains(c2, *i))
			return i;

	return c1.end();
}

template <typename container1, typename container2>
bool contains_one_of(const container1 &c1, const container2 &c2)
{
	return (find_first_of(c1, c2) != c1.end());
}

template <typename container1, typename container2>
typename container1::iterator find_last_of(container1 &c1, const container2 &c2)
{
	for (typename container1::iterator i = c1.rbegin(); i != c1.rend(); i--)
		if (contains(c2, *i))
			return i;

	return c1.rend();
}

template <typename container1, typename container2>
typename container1::const_iterator find_last_of(const container1 &c1, const container2 &c2)
{
	for (typename container1::const_iterator i = c1.rbegin(); i != c1.rend(); i--)
		if (contains(c2, *i))
			return i;

	return c1.rend();
}

template <typename container, typename container2>
array<typename container::iterator> find_all_of(container &c, const container2 &c2)
{
	array<typename container::iterator> results;
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (contains(c2, *i))
			results.push_back(i);

	return results;
}

template <typename container1, typename container2>
bool contains_all_of(const container1 &c1, const container2 &c2)
{
	for (typename container2::const_iterator i = c2.begin(); i != c2.end(); i++)
		if (!contains(c1, *i))
			return false;

	return true;
}

template <typename container, typename container2>
array<typename container::const_iterator> find_all_of(const container &c, const container2 &c2)
{
	array<typename container::const_iterator> results;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		if (contains(c2, *i))
			results.push_back(i);

	return results;
}

template <typename container, typename container2>
int count_all_of(const container &c, const container2 &c2)
{
	int result = 0;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		result += contains(c2, *i);
	return result;
}

template <typename container, typename container2>
typename container::iterator find_first_pattern(container &c, const container2 &t)
{
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
	{
		bool found = true;
		typename container::iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
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
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
	{
		bool found = true;
		typename container::const_iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
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
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
	{
		bool found = true;
		typename container::iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
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
array<typename container::const_iterator> find_all_pattern(const container &c, const container2 &t)
{
	array<typename container::const_iterator> result;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
	{
		bool found = true;
		typename container::const_iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
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
int count_all_pattern(const container &c, const container2 &t)
{
	int result = 0;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
	{
		bool found = true;
		typename container::const_iterator k = i;
		for (typename container2::const_iterator j = t.begin(); j != t.end() && found; j++,k++)
		{
			if (k == c.end())
				return result;
			else
				found = (*k == *j);
		}

		result += found;
	}

	return result;
}

template <typename container, typename element>
typename container::iterator lower_bound(container &c, const element &t, int radix = 2)
{
	return lower_bound(c.begin(), c.end(), t, radix, c.size());
}

template <typename container, typename element>
typename container::const_iterator lower_bound(const container &c, const element &t, int radix = 2)
{
	return lower_bound(c.begin(), c.end(), t, radix, c.size());
}

template <typename iterator, typename element>
iterator lower_bound(iterator start, iterator end, const element &t, int radix = 2, int size = -1)
{
	if (size < 0)
		size = end - start;

	if (size >= radix)
	{
		int D = radix - size;
		for (iterator i = start; i != end; i++)
		{
			if (D > 0)
			{
				if (t <= *(i-1))
					return lower_bound(start, i, t, radix, size/radix);
				start = i;
				D += radix - size;
			}
			else
				D += radix;
		}

		return lower_bound(start, end, t, radix, size%radix);
	}
	else
	{
		iterator i = start;
		while (i != end && *i < t)
			i++;
		return i;
	}
}

template <typename container, typename element>
typename container::iterator upper_bound(container &c, const element &t, int radix = 2)
{
	return upper_bound(c.begin(), c.end(), t, radix, c.size());
}

template <typename container, typename element>
typename container::const_iterator upper_bound(const container &c, const element &t, int radix = 2)
{
	return upper_bound(c.begin(), c.end(), t, radix, c.size());
}

template <typename iterator, typename element>
iterator upper_bound(iterator start, iterator end, const element &t, int radix = 2, int size = -1)
{
	if (size < 0)
		size = end - start;

	if (size >= radix)
	{
		int D = radix - size;
		for (iterator i = start; i != end; i++)
		{
			if (D > 0)
			{
				if (t < *(i-1))
					return upper_bound(start, i, t, radix, size/radix);
				start = i;
				D += radix - size;
			}
			else
				D += radix;
		}

		return upper_bound(start, end, t, radix, size%radix);
	}
	else
	{
		iterator i = start;
		while (i != end && *i <= t)
			i++;
		return i;
	}
}

}

