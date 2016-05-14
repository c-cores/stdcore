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

template <class container>
container collapse(container c)
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
container unique(container c)
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

template <class container>
container remove(container c, const typename container::type &value)
{
	typename container::iterator i = c.begin();
	while (i != c.end())
	{
		if (*i == value)
			i.drop();
		else
			i++;
	}
	return c;
}

template <class container>
container range(typename container::type lower, typename container::type upper, typename container::type step)
{
	if (lower < upper)
	{
		container result;
		for (typename container::type i = lower; i < upper; i += step)
			result.push_back(i);
		return result;
	}
	else
	{
		container result;
		for (typename container::type i = lower; i > upper; i += step)
			result.push_back(i);
		return result;
	}
}

template <class container1, class container2>
container1 intersection(const container1 &c1, const container2 &c2)
{
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
container intersection(const array<container> &c)
{
	typedef typename container::const_iterator iterator_m0;
	typedef typename array<iterator_m0>::iterator iterator_m1;
	typedef typename array<iterator_m1>::iterator iterator_m2;

	container result;
	array<iterator_m0> i;
	i.reserve(c.size());
	for (iterator_m0 j = c.begin(); j; j++)
		i.push_back_unsafe(j->begin());

	bool working = true;
	while (working)
	{
		array<iterator_m1> smallest;
		for (iterator_m1 j = i.begin()+1; j; j++)
		{
			if (smallest.size() == 0 || **j == **smallest.begin())
				smallest.push_back(j);
			else if (**j < **smallest.begin())
			{
				smallest.clear();
				smallest.push_back(j);
			}
		}

		if (smallest.size() == c.size())
			result.push_back(***smallest.begin());

		for (iterator_m2 j = smallest.begin(); j && working; j++)
			working = ++**j;
	}

	return result;
}

template <class container>
int intersection_size(const array<container> &c)
{
	typedef typename container::const_iterator iterator_m0;
	typedef typename array<iterator_m0>::iterator iterator_m1;
	typedef typename array<iterator_m1>::iterator iterator_m2;

	int result = 0;
	array<iterator_m0> i;
	i.reserve(c.size());
	for (iterator_m0 j = c.begin(); j; j++)
		i.push_back_unsafe(j->begin());

	bool working = true;
	while (working)
	{
		array<iterator_m1> smallest;
		for (iterator_m1 j = i.begin()+1; j; j++)
		{
			if (smallest.size() == 0 || **j == **smallest.begin())
				smallest.push_back(j);
			else if (**j < **smallest.begin())
			{
				smallest.clear();
				smallest.push_back(j);
			}
		}

		result += (smallest.size() == c.size());

		for (iterator_m2 j = smallest.begin(); j && working; j++)
			working = ++**j;
	}

	return result;
}

template <class container>
bool intersects(const array<container> &c)
{
	typedef typename container::const_iterator iterator_m0;
	typedef typename array<iterator_m0>::iterator iterator_m1;
	typedef typename array<iterator_m1>::iterator iterator_m2;

	array<iterator_m0> i;
	i.reserve(c.size());
	for (iterator_m0 j = c.begin(); j; j++)
		i.push_back_unsafe(j->begin());

	bool working = true;
	while (working)
	{
		array<iterator_m1> smallest;
		for (iterator_m1 j = i.begin()+1; j; j++)
		{
			if (smallest.size() == 0 || **j == **smallest.begin())
				smallest.push_back(j);
			else if (**j < **smallest.begin())
			{
				smallest.clear();
				smallest.push_back(j);
			}
		}

		if (smallest.size() == c.size())
			return true;

		for (iterator_m2 j = smallest.begin(); j && working; j++)
			working = ++**j;
	}

	return false;
}

template <class container1, class container2>
void symmetric_compliment(container1 &c1, container2 &c2)
{
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

}

