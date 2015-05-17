/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#include "slice.h"

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
	slice<typename container::iterator> b = c.bound();
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

		slice<typename container::iterator> small(b.left, store-1);
		slice<typename container::iterator> big(store+1, b.right);

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

	if (++i != j)
		i.pop(j);

	return c;
}

template <class container>
container &unique(container &c)
{
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		for (typename container::iterator j = i+1; j != c.end();)
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
