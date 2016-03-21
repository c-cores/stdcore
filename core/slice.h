/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

namespace core
{

template <class iterator_type>
struct slice
{
	typedef iterator_type iterator;
	typedef iterator_type const_iterator;

	slice() {}

	slice(iterator left, iterator right)
	{
		this->left = left;
		this->right = right;
	}

	~slice() {}

	iterator left, right;

	int size() const
	{
		return right - left + 1;
	}

	iterator begin() const
	{
		return left;
	}

	iterator end() const
	{
		return right+1;
	}

	iterator rbegin() const
	{
		return right;
	}

	iterator rend() const
	{
		return left-1;
	}

	slice<iterator> &sub(int left, int right = -1) const
	{
		if (right < 0)
			return slice<iterator>(this->left+left, this->right+right+1);
		else
			return slice<iterator>(this->left+left, this->left+right);
	}
};

template <class iterator1, class iterator2>
int compare(slice<iterator1> a, slice<iterator2> b)
{
	iterator1 i = a.left;
	iterator2 j = b.left;
	for (; i != a.right+1 && j != b.right+1; i++, j++)
	{
		if (*i < *j)
			return -1;
		else if (*j < *i)
			return 1;
	}
	if (j != b.right+1)
		return -1;
	else if (i != a.right+1)
		return 1;
	else
		return 0;
}

template <class iterator1, class iterator2>
bool operator==(slice<iterator1> s1, slice<iterator2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class iterator1, class iterator2>
bool operator!=(slice<iterator1> s1, slice<iterator2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class iterator1, class iterator2>
bool operator<(slice<iterator1> s1, slice<iterator2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class iterator1, class iterator2>
bool operator>(slice<iterator1> s1, slice<iterator2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class iterator1, class iterator2>
bool operator<=(slice<iterator1> s1, slice<iterator2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class iterator1, class iterator2>
bool operator>=(slice<iterator1> s1, slice<iterator2> s2)
{
	return (compare(s1, s2) >= 0);
}

}

