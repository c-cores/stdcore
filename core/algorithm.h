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
container &sort_selection(container &c)
{
	slice<typename container::iterator> b = c.bound();
	for (typename container::iterator i = b.left; i != b.right+1; i++)
	{
		typename container::iterator max_j = i;
		for (typename container::iterator j = i+1; j != b.right+1; j++)
			if (*j < *max_j)
				max_j = j;

		i.swap(max_j);
	}

	return c;
}

template <class container>
container &sort_quick(container &c)
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

		slice<typename container::iterator> small(c.begin(), store-1);
		slice<typename container::iterator> big(store+1, c.rbegin());

		sort_quick(small);
		sort_quick(big);
	}
	else if (c.size() > 1)
		if (c.back() < c.front())
			c.begin().swap(c.rbegin());

	return c;
}

template <class container, class container2>
container2 &order_quick(const container &c, container2 &order)
{
	if (order.size() > 2)
	{
		typename container2::iterator pivot = median_iterator(order.begin(), order.begin() + order.size()/2, order.rbegin());

		pivot.swap(order.rbegin());
		pivot = order.rbegin();

		typename container2::iterator store = order.begin();
		for (typename container2::iterator i = order.begin(); i != order.rbegin(); i++)
			if (c.get(*i) < c.get(*pivot))
			{
				i.swap(store);
				store++;
			}

		store.swap(order.rbegin());

		slice<typename container2::iterator> small(order.begin(), store-1);
		slice<typename container2::iterator> big(store+1, order.rbegin());

		order_quick(c, small);
		order_quick(c, big);
	}
	else if (order.size() > 1)
		if (c.get(*order.rbegin()) < c.get(*order.begin()))
			order.begin().swap(order.rbegin());

	return order;
}


template <class container>
bool is_sorted(container &c)
{
	for (typename container::iterator i = c.begin(); i != c.rbegin(); i++)
		if (*(i+1) < *i)
			return false;

	return true;
}

template <class container>
bool is_rsorted(container &c)
{
	for (typename container::iterator i = c.begin(); i != c.rbegin(); i++)
		if (*(i+1) > *i)
			return false;

	return true;
}

template <class container>
container &reverse(container &c)
{
	for (typename container::iterator i = c.begin(), j = c.rbegin(); i != j && i != j+1; i++, j--)
		i.swap(j);
	return c;
}

// Search Algorithms
template <class container>
typename container::iterator find(container &c, const typename container::iterator::type &t)
{
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (*i == t)
			return i;

	return c.end();
}

template <class container>
bool contains(container &c, const typename container::iterator::type &t)
{
	return (find(c, t) != c.end());
}

template <class container>
typename container::iterator search_tree(container &c, const typename container::iterator::type &t, int radix = 2)
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

// Duplicate Removal
template <class container>
container &collapse(container &c)
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
container &unique(container &c)
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

}

