/*
 * container.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#ifndef container_h
#define container_h

namespace core
{

template <class iterator_type>
struct boundary
{
	typedef iterator_type iterator;

	boundary() {}
	boundary(iterator l, iterator r)
	{
		left = l;
		right = r;
	}
	~boundary() {}

	iterator left, right;

	boundary<iterator> sub(int i, int j)
	{
		return boundary<iterator>(left + i, left + j);
	}

	boundary<iterator> &bound()
	{
		return *this;
	}

	template <class iterator2>
	int compare(boundary<iterator2> a) const
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
bool operator==(boundary<iterator1> s1, boundary<iterator2> s2)
{
	return (s1.compare(s2) == 0);
}

template <class iterator1, class iterator2>
bool operator!=(boundary<iterator1> s1, boundary<iterator2> s2)
{
	return (s1.compare(s2) != 0);
}

template <class iterator1, class iterator2>
bool operator<(boundary<iterator1> s1, boundary<iterator2> s2)
{
	return (s1.compare(s2) < 0);
}

template <class iterator1, class iterator2>
bool operator>(boundary<iterator1> s1, boundary<iterator2> s2)
{
	return (s1.compare(s2) > 0);
}

template <class iterator1, class iterator2>
bool operator<=(boundary<iterator1> s1, boundary<iterator2> s2)
{
	return (s1.compare(s2) <= 0);
}

template <class iterator1, class iterator2>
bool operator>=(boundary<iterator1> s1, boundary<iterator2> s2)
{
	return (s1.compare(s2) >= 0);
}

}

#endif
