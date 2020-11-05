/*
 * sort.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <std/search.h>
#include <std/array.h>

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
typename container_type::iterator choseLast(range<typename container_type::iterator> c)
{
	return c.finish-1;
}

template <class container_type>
typename container_type::iterator choseMid(range<typename container_type::iterator> c)
{
	return c.start + c.size()/2;
}

template <class container_type>
typename container_type::iterator choseRand(range<typename container_type::iterator> c)
{
	return c.start + rand()%(c.finish-c.start);
}

template <class container_type>
struct Sort {
	typedef typename container_type::iterator iterator;
	typedef iterator (*PivotFunc)(range<iterator>);
};

template <class container_type>
container_type sort_quick(container_type c, typename Sort<container_type>::PivotFunc chosePivot = &choseLast<container_type>)
{
	typedef range<typename container_type::iterator> section_t;
	core::array<section_t> stack;
	if (c.begin() != c.end() and c.begin()+1 != c.end())
		stack.push_back(section_t(c.begin(), c.end()));

	while (stack.size() > 0) {
		section_t r = stack.back();
		stack.drop_back();

		if (r.start+2 == r.finish) {
			if (*r.start > *(r.start+1))
				r.start.swap(r.start+1);
		} else {
			typename container_type::iterator pivot = chosePivot(r);
			if (pivot != r.finish-1) {
				pivot.swap(r.finish-1);
				pivot = r.finish-1;
			}

			typename container_type::iterator store = r.start;
			for (typename container_type::iterator i = r.start; i != pivot and i != r.finish; i++)
				if (*i < *pivot)
				{
					if (i != store)
						i.swap(store);
					store++;
				}

			if (store != pivot) {
				store.swap(pivot);
				pivot = store;
			}

			if (r.start != store and r.start+1 != store)
				stack.push_back(section_t(r.start, store));
			store++;

			while (store != r.finish and *store == *pivot)
				store++;

			if (store != r.finish and store+1 != r.finish)
				stack.push_back(section_t(store, r.finish));
		}
	}

	return c;
}

template <class container_type>
container_type &sort_quick_inplace(container_type &c, typename Sort<container_type>::PivotFunc chosePivot = &choseLast<container_type>)
{
	typedef range<typename container_type::iterator> section_t;
	core::array<section_t> stack;
	if (c.begin() != c.end() and c.begin()+1 != c.end())
		stack.push_back(section_t(c.begin(), c.end()));

	while (stack.size() > 0) {
		section_t r = stack.back();
		stack.drop_back();

		if (r.start+2 == r.finish) {
			if (*r.start > *(r.start+1))
				r.start.swap(r.start+1);
		} else {
			typename container_type::iterator pivot = chosePivot(r);
			if (pivot != r.finish-1) {
				pivot.swap(r.finish-1);
				pivot = r.finish-1;
			}

			typename container_type::iterator store = r.start;
			for (typename container_type::iterator i = r.start; i != pivot and i != r.finish; i++)
				if (*i < *pivot)
				{
					if (i != store)
						i.swap(store);
					store++;
				}

			if (store != pivot) {
				store.swap(pivot);
				pivot = store;
			}

			if (r.start != store and r.start+1 != store)
				stack.push_back(section_t(r.start, store));
			store++;

			while (store != r.finish and *store == *pivot)
				store++;

			if (store != r.finish and store+1 != r.finish)
				stack.push_back(section_t(store, r.finish));
		}
	}

	return c;
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

template <class container_type, class element>
typename container_type::iterator sort_unique_insert(container_type &c1, const element &c2)
{
	typename container_type::iterator result = lower_bound(c1, c2);
	if (result and c2 == result.get()) {
		return result;
	} else {
		result.push(c2);
		return result-1;
	}
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

template <class container_type1, class container_type2>
container_type1 &sort_unique_merge_inplace(container_type1 &c1, const container_type2 &c2)
{
	typename container_type2::const_iterator j = c2.begin();
	if (j) {
		typename container_type1::iterator i = lower_bound(c1, *j);
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
				j++;
			}
		}

		c1.append_back(j.sub());
	}
	return c1;
}

}

