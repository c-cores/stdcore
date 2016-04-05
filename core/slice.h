/*
 * slice.h
 *
 *  Created on: Oct 13, 2014
 *      Author: nbingham
 */

#pragma once

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
		right = copy.rbegin();
	}

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

	slice<container> sub(int left, int right = -1) const
	{
		if (right < 0)
			return slice<container>(this->left+left, this->right+right+1);
		else
			return slice<container>(this->left+left, this->left+right);
	}

	static slice<container> sub(iterator left, iterator right)
	{
		return slice<container>(left, right);
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
		right = copy.rbegin();
	}

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

	slice<const container> sub(int left, int right = -1) const
	{
		if (right < 0)
			return slice<const container>(this->left+left, this->right+right+1);
		else
			return slice<const container>(this->left+left, this->left+right);
	}

	static slice<const container> sub(iterator left, iterator right)
	{
		return slice<const container>(left, right);
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

	slice<value_type*> sub(int left, int right = -1) const
	{
		if (right < 0)
			return slice<value_type*>(this->left+left, this->right+right+1);
		else
			return slice<value_type*>(this->left+left, this->left+right);
	}

	static slice<value_type*> sub(value_type* left, value_type* right)
	{
		return slice<value_type*>(left, right);
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

