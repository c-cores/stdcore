/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

namespace core
{

template <typename value_type, typename container_iterator, typename container_const_iterator>
struct container
{
	typedef value_type type;
	typedef container_iterator iterator;
	typedef container_const_iterator const_iterator;

	container() {}
	virtual ~container() {};
	
	virtual const_iterator begin() const = 0;
	virtual const_iterator end() const = 0;
	virtual const_iterator rbegin() const = 0;
	virtual const_iterator rend() const = 0;
};

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool compare(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	ci0 i = a.begin();
	ci1 j = b.begin();
	for (; i && j; i++, j++)
	{
		if (*i < *j)
			return -1;
		else if (*j < *i)
			return 1;
	}
	if (j)
		return -1;
	else if (i)
		return 1;
	else
		return 0;
}

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool operator==(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	ci0 i = a.begin();
	ci1 j = b.begin();
	for (; i && j; i++, j++)
		if (!(*i == *j))
			return false;

	return !(i || j);
}

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool operator!=(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	return !(a == b);
}

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool operator<(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	ci0 i = a.begin();
	ci1 j = b.begin();
	for (; i && j; i++, j++)
	{
		if (*i < *j)
			return true;
		else if (!(*i == *j))
	    	return false;
	}

	return j;
}

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool operator>(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	ci0 i = a.begin();
	ci1 j = b.begin();
	for (; i && j; i++, j++)
	{
		if (*i > *j)
			return true;
		else if (!(*i == *j))
	    	return false;
	}

	return i;
}

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool operator<=(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	return !(a > b);
}

template<typename v0, typename i0, typename ci0, typename v1, typename i1, typename ci1>
bool operator>=(const container<v0, i0, ci0> &a, const container<v1, i1, ci1> &b)
{
	return !(a < b);
}

}

