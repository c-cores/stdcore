/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>
#include <core/ascii_stream.h>
#include <core/search.h>

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
container &sort_selection_inplace(container &c)
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
container sort_quick(container c, typename container::iterator pivot = typename container::iterator())
{
	if (c.begin() == c.end() || c.begin()+1 == c.end())
		return c;
	else if (c.begin()+2 == c.end())
	{
		if (*c.rbegin() < *c.begin())
			c.begin().swap(c.rbegin());
		return c;
	}
	else
	{
		if (pivot)
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
		return c;
	}
}

template <class container>
container &sort_quick_inplace(container &c, typename container::iterator pivot = typename container::iterator())
{
	if (c.begin() == c.end() || c.begin()+1 == c.end())
		return c;
	else if (c.begin()+2 == c.end())
	{
		if (*c.rbegin() < *c.begin())
			c.begin().swap(c.rbegin());
		return c;
	}
	else
	{
		if (pivot)
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

		return c;
	}
}

template <class container1, class container2>
container1 sort_merge(const container1 &c1, const container1 &c2)
{
	container1 result;
	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i != c1.end() && j != c2.end())
	{
		if (*i < *j)
		{
			result.push_back(*i);
			i++;
		}
		else if (*j < *i)
		{
			result.push_back(*j);
			j++;
		}
		else
		{
			result.push_back(*i);
			result.push_back(*j);
			i++;
			j++;
		}
	}

	result.append_back(i.sub());
	result.append_back(j.sub());
	return result;
}

template <class container1, class container2>
container1 &sort_merge_inplace(container1 &c1, const container1 &c2)
{
	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i != c1.end() && j != c2.end())
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
		{
			i.push(*j);
			j++;
		}
		else
		{
			i++;
			i.push(*j);
			j++;
		}
	}

	c1.append_back(j.sub());
	return c1;
}

template <class container, class element>
typename container::iterator &sort_insert(container &c1, const element &c2)
{
	typename container::iterator result = lower_bound(c1, c2);
	result.push(c2);
	return result-1;
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

template <class container>
container &reverse_inplace(container &c)
{
	for (typename container::iterator i = c.begin(), j = c.rbegin(); i != j && i != j+1; i++, j--)
		i.swap(j);
	return c;
}

}

