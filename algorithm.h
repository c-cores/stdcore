/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#include "container.h"

#ifndef algorithm_h
#define algorithm_h

namespace core
{

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
	boundary<typename container::iterator> b = c.bound();
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
	boundary<typename container::iterator> b = c.bound();
	int size = (b.right + 1) - b.left;
	if (size > 2)
	{
		typename container::iterator pivot = median_iterator(b.left, b.left + size/2, b.right);

		pivot.swap(b.right);
		pivot = b.right;

		typename container::iterator store = b.left;
		for (typename container::iterator i = b.left; i != b.right; i++)
			if (*i < *pivot)
			{
				i.swap(store);
				store++;
			}

		store.swap(b.right);

		boundary<typename container::iterator> small(b.left, store-1);
		boundary<typename container::iterator> big(store+1, b.right);

		sort_quick(small);
		sort_quick(big);
	}
	else if (size > 1)
		if (*b.right < *b.left)
			b.left.swap(b.right);

	return c;
}

template <class container>
bool is_sorted(container &c)
{
	boundary<typename container::iterator> b = c.bound();
	for (typename container::iterator i = b.left; i != b.right-1; i++)
		if (*(i+1) < *i)
			return false;

	return true;
}

template <class container>
bool is_rsorted(container &c)
{
	boundary<typename container::iterator> b = c.bound();
	for (typename container::iterator i = b.left; i != b.right-1; i++)
		if (*(i+1) > *i)
			return false;

	return true;
}

template <class container>
container &reverse(container &c)
{
	boundary<typename container::iterator> b = c.bound();
	for (typename container::iterator i = b.left, j = b.right; i != j && i != j+1; i++, j--)
		i.swap(j);
	return c;
}

// Search Algorithms
template <class container>
typename container::iterator find(container &c, const typename container::iterator::type &t)
{
	boundary<typename container::iterator> b = c.bound();
	for (typename container::iterator i = b.left; i != b.right+1; i++)
		if (*i == t)
			return i;

	return b.right+1;
}

template <class container>
bool contains(container &c, const typename container::iterator::type &t)
{
	boundary<typename container::iterator> b = c.bound();
	return (find(b, t) != b.right+1);
}

template <class container>
typename container::iterator search_tree(container &c, const typename container::iterator::type &t, int radix = 2)
{
	boundary<typename container::iterator> b = c.bound();
	int size = b.right - b.left + 1;
	if (size > 0)
	{
		int step = size/radix;
		boundary<typename container::iterator> pivot(b.left, b.left + (step-1));
		for (int i = 0; i < radix-1; i++)
		{
			if (*pivot.right < t)
				return search_tree(pivot, t, radix);

			pivot.left = pivot.right+1;
			pivot.right = pivot.left + (step-1);
		}

		pivot.right = b.right;
		return search_tree(pivot, t, radix);
	}
	else
		return b.left;
}

// Duplicate Removal
template <class container>
container &collapse(container &c)
{
	boundary<typename container::iterator> b = c.bound();
	typename container::iterator i = b.left, j = b.left+1;
	for (; j != b.right+1; j++)
		if (!(*i == *j) && ++i != j)
			*i = *j;

	if (++i != j)
		i.pop(j);

	return c;
}

template <class container>
container &unique(container &c)
{
	boundary<typename container::iterator> b = c.bound();
	for (typename container::iterator i = b.left; i != b.right+1; i++)
		for (typename container::iterator j = i+1; j != b.right+1;)
		{
			if (*i == *j)
				j.pop();
			else
				j++;
		}

	return c;
}

}

#endif
