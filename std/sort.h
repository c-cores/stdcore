/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/search.h>

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
template <class container_type>
container_type sort_selection(container_type c)
{
	for (typename container_type::iterator i = c.begin(); i != c.end(); i++)
	{
		typename container_type::iterator max_j = i;
		for (typename container_type::iterator j = i+1; j != c.end(); j++)
			if (*j < *max_j)
				max_j = j;

		i.swap(max_j);
	}

	return c;
}

template <class container_type>
container_type &sort_selection_inplace(container_type &c)
{
	for (typename container_type::iterator i = c.begin(); i != c.end(); i++)
	{
		typename container_type::iterator max_j = i;
		for (typename container_type::iterator j = i+1; j != c.end(); j++)
			if (*j < *max_j)
				max_j = j;

		i.swap(max_j);
	}

	return c;
}

template <class container_type>
container_type sort_quick(container_type c, typename container_type::iterator pivot = typename container_type::iterator())
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

		typename container_type::iterator store = c.begin();
		for (typename container_type::iterator i = c.begin(); i != c.rbegin() && i != c.end(); i++)
			if (*i < *pivot)
			{
				i.swap(store);
				store++;
			}

		store.swap(c.rbegin());

		sort_quick(slice_t(c.begin(), store));
		sort_quick(slice_t(store+1, c.end()));
		return c;
	}
}

template <class container_type>
container_type &sort_quick_inplace(container_type &c, typename container_type::iterator pivot = typename container_type::iterator())
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

		typename container_type::iterator store = c.begin();
		for (typename container_type::iterator i = c.begin(); i != c.rbegin() && i != c.end(); i++)
			if (*i < *pivot)
			{
				i.swap(store);
				store++;
			}

		store.swap(c.rbegin());

		sort_quick(slice_t(c.begin(), store));
		sort_quick(slice_t(store+1, c.end()));

		return c;
	}
}

template <class container_type1, class container_type2>
container_type1 sort_merge(const container_type1 &c1, const container_type2 &c2)
{
	container_type1 result;
	typename container_type1::const_iterator i = c1.begin();
	typename container_type2::const_iterator j = c2.begin();
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

template <class container_type1, class container_type2>
container_type1 &sort_merge_inplace(container_type1 &c1, const container_type2 &c2)
{
	typename container_type1::iterator i = c1.begin();
	typename container_type2::const_iterator j = c2.begin();
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

template <class container_type, class element>
typename container_type::iterator sort_insert(container_type &c1, const element &c2)
{
	typename container_type::iterator result = lower_bound(c1, c2);
	result.push(c2);
	return result-1;
}

template <class container_type>
bool is_sorted(const container_type &c)
{
	for (typename container_type::const_iterator i = c.begin(); i != c.rbegin(); i++)
		if (*(i+1) < *i)
			return false;

	return true;
}

template <class container_type>
bool is_rsorted(const container_type &c)
{
	for (typename container_type::const_iterator i = c.begin(); i != c.rbegin(); i++)
		if (*(i+1) > *i)
			return false;

	return true;
}

template <class container_type>
container_type reverse(container_type c)
{
	for (typename container_type::iterator i = c.begin(), j = c.rbegin(); i != j && i != j+1; i++, j--)
		i.swap(j);
	return c;
}

template <class container_type>
container_type &reverse_inplace(container_type &c)
{
	for (typename container_type::iterator i = c.begin(), j = c.rbegin(); i != j && i != j+1; i++, j--)
		i.swap(j);
	return c;
}

}

