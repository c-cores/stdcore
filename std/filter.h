/*
 * filter.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/array.h>
#include <std/search.h>

namespace core
{

template <typename container, typename element>
array<typename container::iterator> filter(container &c, const element &t)
{
	array<typename container::iterator> results;
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container, typename element>
array<typename container::const_iterator> filter(const container &c, const element &t)
{
	array<typename container::const_iterator> results;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			results.push_back(i);

	return results;
}

template <typename container, typename container2>
array<typename container::iterator> filter_each(container &c, const container2 &c2)
{
	array<typename container::iterator> results;
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (contains(c2, *i))
			results.push_back(i);

	return results;
}

template <typename container, typename container2>
array<typename container::const_iterator> filter_each(const container &c, const container2 &c2)
{
	array<typename container::const_iterator> results;
	for (typename container::const_iterator i = c.begin(); i != c.end(); i++)
		if (contains(c2, *i))
			results.push_back(i);

	return results;
}

template <typename container, typename container2>
array<typename container::iterator> filter_pattern(container &c, const container2 &t)
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
array<typename container::const_iterator> filter_pattern(const container &c, const container2 &t)
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

}

