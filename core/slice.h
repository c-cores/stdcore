/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

#include <memory.h>

namespace core
{

template <class container>
struct slice
{
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator const_iterator;
	typedef typename container::type type;

	slice() {}

	slice(container &copy)
	{
		left = copy.begin();
		right = copy.end();
	}

	slice(iterator start, iterator end)
	{
		left = start;
		right = end;
	}

	~slice() {}

	iterator left, right;

	int size() const
	{
		return right - left;
	}

	iterator begin() const
	{
		return left;
	}

	iterator end() const
	{
		return right;
	}

	iterator rbegin() const
	{
		return right-1;
	}

	iterator rend() const
	{
		return left-1;
	}

	slice<container> sub(int start, int end) const
	{
		iterator l = start < 0 ? right+start : left+start;
		iterator r = end < 0 ? right+end : left+end;
		return slice<container>(l, r);
	}

	slice<container> sub(int start) const
	{
		iterator l = start < 0 ? right+start : left+start;
		return slice<container>(l, right);
	}

	static slice<container> sub(iterator start, iterator end)
	{
		return slice<container>(start, end);
	}

	slice<container> ref() const
	{
		return *this;
	}
};

template <class container>
struct slice<const container>
{
	typedef typename container::const_iterator iterator;
	typedef typename container::const_iterator const_iterator;
	typedef typename container::type type;

	slice() {}

	slice(const container &copy)
	{
		left = copy.begin();
		right = copy.end();
	}

	slice(iterator start, iterator end)
	{
		left = start;
		right = end;
	}

	~slice() {}

	iterator left, right;

	int size() const
	{
		return right - left;
	}

	iterator begin() const
	{
		return left;
	}
	
	iterator end() const
	{
		return right;
	}

	iterator rbegin() const
	{
		return right-1;
	}

	iterator rend() const
	{
		return left-1;
	}

	slice<container> sub(int start, int end) const
	{
		iterator l = start < 0 ? right+start : left+start;
		iterator r = end < 0 ? right+end : left+end;
		return slice<container>(l, r);
	}

	slice<container> sub(int start) const
	{
		iterator l = start < 0 ? right+start : left+start;
		return slice<container>(l, right);
	}

	static slice<container> sub(iterator start, iterator end)
	{
		return slice<container>(start, end);
	}

	slice<const container> ref() const
	{
		return *this;
	}
};

template <class value_type>
struct slice<value_type*>
{
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type type;

	slice() { left = NULL; right = NULL; }

	slice(iterator start, iterator end)
	{
		left = start;
		right = end;
	}

	~slice() {}

	iterator left, right;

	int size() const
	{
		return right - left;
	}

	iterator begin() const
	{
		return left;
	}

	iterator end() const
	{
		return right;
	}

	iterator rbegin() const
	{
		return right-1;
	}

	iterator rend() const
	{
		return left-1;
	}

	slice<value_type*> sub(int start, int end) const
	{
		iterator l = start < 0 ? right+start : left+start;
		iterator r = end < 0 ? right+end : left+end;
		return slice<value_type*>(l, r);
	}

	slice<value_type*> sub(int start) const
	{
		iterator l = start < 0 ? right+start : left+start;
		return slice<value_type*>(l, right);
	}

	static slice<value_type*> sub(iterator start, iterator end)
	{
		return slice<value_type*>(start, end);
	}

	slice<value_type*> ref() const
	{
		return *this;
	}
};

template <class container1, class container2>
int compare(const container1 &a, const container2 &b)
{
	typename container1::const_iterator i = a.begin();
	typename container2::const_iterator j = b.begin();
	for (; i != a.end() && j != b.end(); i++, j++)
	{
		if (*i < *j)
			return -1;
		else if (*j < *i)
			return 1;
	}
	if (j != b.end())
		return -1;
	else if (i != a.end())
		return 1;
	else
		return 0;
}

template <class container1, class container2>
bool operator==(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) == 0);
}

template <class container1, class container2>
bool operator!=(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) != 0);
}

template <class container1, class container2>
bool operator<(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) < 0);
}

template <class container1, class container2>
bool operator>(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) > 0);
}

template <class container1, class container2>
bool operator<=(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) <= 0);
}

template <class container1, class container2>
bool operator>=(slice<container1> s1, slice<container2> s2)
{
	return (compare(s1, s2) >= 0);
}

}

