/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#ifndef slice_h
#define slice_h

namespace core
{

template <class iterator_type>
struct slice
{
	typedef iterator_type iterator;

	slice() {}
	slice(iterator l, iterator r)
	{
		left = l;
		right = r;
	}

	~slice() {}

	iterator left, right;

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

	slice<iterator> &bound()
	{
		return *this;
	}

	//slice<iterator> sub(int i, int j)
	//{
	//	return slice<iterator>(left + i, left + j);
	//}

	template <class iterator2>
	int compare(slice<iterator2> a) const
	{
		iterator i = left;
		iterator2 j = a.left;
		for (; i != right+1 && j != a.right+1; i++, j++)
		{
			if (*i < *j)
				return -1;
			else if (*i > *j)
				return 1;
		}

		if (j != a.right+1)
			return -1;
		else if (i != right+1)
			return 1;
		else
			return 0;
	}
};

template <class iterator1, class iterator2>
bool operator==(slice<iterator1> s1, slice<iterator2> s2)
{
	return (s1.compare(s2) == 0);
}

template <class iterator1, class iterator2>
bool operator!=(slice<iterator1> s1, slice<iterator2> s2)
{
	return (s1.compare(s2) != 0);
}

template <class iterator1, class iterator2>
bool operator<(slice<iterator1> s1, slice<iterator2> s2)
{
	return (s1.compare(s2) < 0);
}

template <class iterator1, class iterator2>
bool operator>(slice<iterator1> s1, slice<iterator2> s2)
{
	return (s1.compare(s2) > 0);
}

template <class iterator1, class iterator2>
bool operator<=(slice<iterator1> s1, slice<iterator2> s2)
{
	return (s1.compare(s2) <= 0);
}

template <class iterator1, class iterator2>
bool operator>=(slice<iterator1> s1, slice<iterator2> s2)
{
	return (s1.compare(s2) >= 0);
}

}

#endif
