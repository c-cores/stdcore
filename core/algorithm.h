/*
 * algorithm.h
 *
 *  Created on: Oct 7, 2014
 *      Author: nbingham
 */

#pragma once

#include <core/slice.h>

#ifdef DEBUG
#include <stdlib.h>
#include <stdio.h>
#endif

namespace core
{

/*!
 * \brief Collapse multiple consecutive duplicate elements into one element.
 *
 * This looks for consecutive elements with the same value and removes all
 * but one in place.
 *
 * \param[inout] c The container to collapse.
 * \return the collapsed version of the container
 * \sa unique
 */
template <class container>
container &collapse_inplace(container &c)
{
	typename container::iterator i = c.begin(), j = c.begin()+1;
	for (; j; j++)
		if (!(*i == *j) && ++i != j)
			*i = *j;

	if (++i)
		c.drop(i, c.end());

	return c;
}

/*!
 * \brief Collapse multiple consecutive duplicate elements into one element.
 *
 * This makes a copy of the input container, then looks for consecutive
 * elements with the same value and removes all but one.
 *
 * \param[inout] c The container to collapse.
 * \return the collapsed version of the container
 * \sa unique
 */
template <class container>
container collapse(container c)
{
	typename container::iterator i = c.begin(), j = c.begin()+1;
	for (; j; j++)
		if (!(*i == *j) && ++i != j)
			*i = *j;

	if (++i)
		c.drop(i, c.end());

	return c;
}

/*!
 * \brief Remove all duplicates leaving only the first occurrence of each value.
 *
 * This looks for elements with the same value and removes all but the first
 * one.
 *
 * \param[inout] c The container to collapse.
 * \return the collapsed version of the container
 * \sa unique
 */
template <class container>
container &unique_inplace(container &c)
{
	for (typename container::iterator i = c.begin(); i; i++)
		for (typename container::iterator j = i+1; j;)
		{
			if (*i == *j)
				j.drop();
			else
				j++;
		}

	return c;
}

/*!
 * \brief Remove all duplicates leaving only the first occurrence of each value.
 *
 * This makes a copy of the input container, then looks for elements with the
 * same value and removes all but the first one.
 *
 * \param[inout] c The container to collapse.
 * \return the collapsed version of the container
 * \sa unique
 */
template <class container>
container unique(container c)
{
	for (typename container::iterator i = c.begin(); i; i++)
		for (typename container::iterator j = i+1; j;)
		{
			if (*i == *j)
				j.drop();
			else
				j++;
		}

	return c;
}

template <class container1, class container2>
container1 intersection(const container1 &c1, const container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	container1 result;
	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i && j)
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
			j++;
		else
		{
			result.push_back(*i);
			i++;
			j++;
		}
	}
	return result;
}

template <class container1, class container2>
int intersection_size(const container1 &c1, const container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	int result = 0;
	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i && j)
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
			j++;
		else
		{
			result++;
			i++;
			j++;
		}
	}
	return result;
}

template <class container1, class container2>
bool intersects(const container1 &c1, const container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i && j)
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
			j++;
		else
			return true;
	}
	return false;
}

template <class container1, class container2, class container3>
container1 intersection(const container1 &c1, const container2 &c2, const container3 &c3)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c3))
		printf("%s:%s:%d error: c3 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	container1 result;
	typename container1::const_iterator i = c1.begin();
	typename container1::const_iterator j = c2.begin();
	typename container1::const_iterator k = c3.begin();
	while (i && j && k)
	{
		if ((*i <= *j && *i < *k) || (*i < *j && *i <= *k))
			i++;
		else if ((*j <= *i && *j < *k) || (*j < *i && *j <= *k))
			j++;
		else if ((*k <= *j && *k < *i) || (*k < *j && *k <= *i))
			k++;
		else
		{
			result.push_back(*i);
			i++;
			j++;
			k++;
		}
	}
	return result;
}

template <class container1, class container2, class container3>
int intersection_size(const container1 &c1, const container2 &c2, const container3 &c3)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c3))
		printf("%s:%s:%d error: c3 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	int result = 0;
	typename container1::const_iterator i = c1.begin();
	typename container1::const_iterator j = c2.begin();
	typename container1::const_iterator k = c3.begin();
	while (i && j && k)
	{
		if ((*i <= *j && *i < *k) || (*i < *j && *i <= *k))
			i++;
		else if ((*j <= *i && *j < *k) || (*j < *i && *j <= *k))
			j++;
		else if ((*k <= *j && *k < *i) || (*k < *j && *k <= *i))
			k++;
		else
		{
			result++;
			i++;
			j++;
			k++;
		}
	}
	return result;
}

template <class container1, class container2, class container3>
bool intersects(const container1 &c1, const container2 &c2, const container3 &c3)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c3))
		printf("%s:%s:%d error: c3 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	typename container1::const_iterator i = c1.begin();
	typename container1::const_iterator j = c2.begin();
	typename container1::const_iterator k = c3.begin();
	while (i && j && k)
	{
		if ((*i <= *j && *i < *k) || (*i < *j && *i <= *k))
			i++;
		else if ((*j <= *i && *j < *k) || (*j < *i && *j <= *k))
			j++;
		else if ((*k <= *j && *k < *i) || (*k < *j && *k <= *i))
			k++;
		else
			return true;
	}
	return false;
}

template <class container>
typename container::type intersection(const container &c)
{
#ifdef DEBUG
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (!is_sorted(*i))
			printf("%s:%s:%d error: c[%d] should be sorted.\n", __FILE__, __FUNCTION__, __LINE__, i.idx());
#endif

	typedef typename container::const_iterator iterator;

	typedef typename container::type type;
	typedef typename type::const_iterator iterator_m0;
	typedef typename array<iterator_m0>::iterator iterator_m1;
	typedef typename array<iterator_m1>::iterator iterator_m2;

	type result;
	array<iterator_m0> i;
	for (iterator j = c.begin(); j; j++)
		i.push_back(j->begin());

	bool working = true;
	array<iterator_m1> smallest;
	while (working)
	{
		bool found = true;
		for (iterator_m1 j = i.begin(); j; j++)
		{
			if (smallest.begin() == smallest.end() || **j == ***smallest.begin())
				smallest.push_back(j);
			else if (**j < ***smallest.begin())
			{
				smallest.clear();
				smallest.push_back(j);
				found = false;
			}
			else
				found = false;
		}

		if (found)
			result.push_back(***smallest.begin());

		for (iterator_m2 j = smallest.begin(); j && working; j++)
			working = ++**j;

		smallest.clear();
	}

	return result;
}

template <class container>
int intersection_size(const container &c)
{
#ifdef DEBUG
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (!is_sorted(*i))
			printf("%s:%s:%d error: c[%d] should be sorted.\n", __FILE__, __FUNCTION__, __LINE__, i.idx());
#endif

	typedef typename container::const_iterator iterator;

	typedef typename container::type type;
	typedef typename type::const_iterator iterator_m0;
	typedef typename array<iterator_m0>::iterator iterator_m1;
	typedef typename array<iterator_m1>::iterator iterator_m2;

	int result = 0;
	array<iterator_m0> i;
	for (iterator j = c.begin(); j; j++)
		i.push_back(j->begin());

	bool working = true;
	array<iterator_m1> smallest;
	while (working)
	{
		bool found = true;
		for (iterator_m1 j = i.begin(); j; j++)
		{
			if (smallest.begin() == smallest.end() || **j == ***smallest.begin())
				smallest.push_back(j);
			else if (**j < ***smallest.begin())
			{
				smallest.clear();
				smallest.push_back(j);
				found = false;
			}
			else
				found = false;
		}

		if (found)
			result++;

		for (iterator_m2 j = smallest.begin(); j && working; j++)
			working = ++**j;

		smallest.clear();
	}

	return result;
}

template <class container>
bool intersects(const container &c)
{
#ifdef DEBUG
	for (typename container::iterator i = c.begin(); i != c.end(); i++)
		if (!is_sorted(*i))
			printf("%s:%s:%d error: c[%d] should be sorted.\n", __FILE__, __FUNCTION__, __LINE__, i.idx());
#endif

	typedef typename container::const_iterator iterator;

	typedef typename container::type type;
	typedef typename type::const_iterator iterator_m0;
	typedef typename array<iterator_m0>::iterator iterator_m1;
	typedef typename array<iterator_m1>::iterator iterator_m2;

	array<iterator_m0> i;
	for (iterator j = c.begin(); j; j++)
		i.push_back(j->begin());

	bool working = true;
	array<iterator_m1> smallest;
	while (working)
	{
		bool found = true;
		for (iterator_m1 j = i.begin(); j; j++)
		{
			if (smallest.begin() == smallest.end() || **j == ***smallest.begin())
				smallest.push_back(j);
			else if (**j < ***smallest.begin())
			{
				smallest.clear();
				smallest.push_back(j);
				found = false;
			}
			else
				found = false;
		}

		if (found)
			return true;

		for (iterator_m2 j = smallest.begin(); j && working; j++)
			working = ++**j;

		smallest.clear();
	}

	return false;
}

template <class container1, class container2>
void symmetric_compliment(container1 &c1, container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	typename container1::iterator i = c1.begin();
	typename container2::iterator j = c2.begin();
	while (i && j)
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
			j++;
		else
		{
			i.drop();
			j.drop();
		}
	}
}

template <class container1, class container2>
container1 difference(const container1 &c1, const container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	container1 result;
	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i && j)
	{
		if (*i < *j)
		{
			result.push_back(*i);
			i++;
		}
		else if (*j < *i)
			j++;
		else
		{
			i++;
			j++;
		}
	}

	result.append_back(i.sub());

	return result;
}

template <class container1, class container2>
bool is_subset(const container1 &c1, const container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	typename container1::const_iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i != c1.end() && j != c2.end())
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
			return false;
		else
		{
			i++;
			j++;
		}
	}

	return j == c2.end();
}

template <typename container, typename value_type>
void remove(container &c, value_type value)
{
	for (typename container::iterator i = c.rbegin(); i != c.rend(); i--)
		if (*i == value)
			i.drop();
}

template <typename container1, typename container2>
void remove_all(container1 &c1, const container2 &c2)
{
#ifdef DEBUG
	if (!is_sorted(c1))
		printf("%s:%s:%d error: c1 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
	if (!is_sorted(c2))
		printf("%s:%s:%d error: c2 should be sorted.\n", __FILE__, __FUNCTION__, __LINE__);
#endif

	typename container1::iterator i = c1.begin();
	typename container2::const_iterator j = c2.begin();
	while (i != c1.end() && j != c2.end())
	{
		if (*i < *j)
			i++;
		else if (*j < *i)
			j++;
		else
			i.drop();
	}
}

}

